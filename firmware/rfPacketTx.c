/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/***** Includes *****/
#include <stdlib.h>
#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* Drivers */
#include <ti/drivers/rf/RF.h>
#include <ti/drivers/PIN.h>

/* Board Header files */
#include "Board.h"
#include "smartrf_settings/smartrf_settings.h"

/* Pin driver handle */
static PIN_Handle ledPinHandle;
static PIN_State ledPinState;

/*
 * Application LED pin configuration table:
 *   - All LEDs board LEDs are off.
 */
PIN_Config pinTable[] =
{
    Board_PIN_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};


/***** Defines *****/
#define TX_TASK_STACK_SIZE 1024
#define TX_TASK_PRIORITY   2

/* Packet TX Configuration */
#define PAYLOAD_LENGTH      30
#define PACKET_INTERVAL     (uint32_t)(4000000*0.5f) /* Set packet interval to 500ms */

#define AES_ECB_LENGTH      16



/***** Prototypes *****/
static void txTaskFunction(UArg arg0, UArg arg1);



/***** Variable declarations *****/
static Task_Params txTaskParams;
Task_Struct txTask;    /* not static so you can see in ROV */
static uint8_t txTaskStack[TX_TASK_STACK_SIZE];

static RF_Object rfObject;
static RF_Handle rfHandle;

uint32_t curtime;
static uint8_t packet[PAYLOAD_LENGTH];
static uint16_t seqNumber;
static PIN_Handle pinHandle;

uint16_t adcValue;
uint32_t uvAdcValue;

typedef struct
{
  uint8_t key[16];                      // Stores the Aes Key
  CryptoCC26XX_KeyLocation keyLocation; // Location in Key RAM
  uint8_t clearText[AES_ECB_LENGTH];    // Input message - cleartext
  uint8_t msgOut[AES_ECB_LENGTH];       // Output message
} AESECBExample;

AESECBExample ecbExample =
{
  { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
  0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C },
  CRYPTOCC26XX_KEY_0,
  {'t','h','i','s','i','s','a','p','l','a','i','n','t','e','x','t'},
  { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
};

CryptoCC26XX_Handle             handle;
int32_t                         keyIndex;
int32_t                         status;
CryptoCC26XX_AESECB_Transaction trans;

/***** Function definitions *****/
void TxTask_init(PIN_Handle inPinHandle)
{
    pinHandle = inPinHandle;

    Task_Params_init(&txTaskParams);
    txTaskParams.stackSize = TX_TASK_STACK_SIZE;
    txTaskParams.priority = TX_TASK_PRIORITY;
    txTaskParams.stack = &txTaskStack;
    txTaskParams.arg0 = (UInt)1000000;

    Task_construct(&txTask, txTaskFunction, &txTaskParams, NULL);
}

static void txTaskFunction(UArg arg0, UArg arg1)
{
    uint32_t curtime;
    RF_Params rfParams;
    RF_Params_init(&rfParams);

    ADC_Handle adc;
    ADC_Params params;

    ADC_Params_init(&params);

    RF_cmdPropTx.pktLen = PAYLOAD_LENGTH;
    RF_cmdPropTx.pPkt = packet;
    RF_cmdPropTx.startTrigger.triggerType = TRIG_ABSTIME;
    RF_cmdPropTx.startTrigger.pastTrig = 1;
    RF_cmdPropTx.startTime = 0;

    /* Request access to the radio */
    rfHandle = RF_open(&rfObject, &RF_prop, (RF_RadioSetup*)&RF_cmdPropRadioDivSetup, &rfParams);

    /* Set the frequency */
    RF_postCmd(rfHandle, (RF_Op*)&RF_cmdFs, RF_PriorityNormal, NULL, 0);

    /* Get current time */
    curtime = RF_getCurrentTime();
    while(1)
    {

        // Attempt to open CryptoCC26XX.
        handle = CryptoCC26XX_open(Board_CRYPTO, false, NULL);
        if (!handle) {
          System_abort("Crypto module could not be opened.");
        }
        keyIndex = CryptoCC26XX_allocateKey(handle, ecbExample.keyLocation,
                                                                           (const uint32_t *) ecbExample.key);
        if (keyIndex == CRYPTOCC26XX_STATUS_ERROR) {
                System_abort("Key Location was not allocated.");
        }
        // Initialize transaction
        CryptoCC26XX_Transac_init((CryptoCC26XX_Transaction *) &trans, CRYPTOCC26XX_OP_AES_ECB_ENCRYPT);
        // Setup transaction
        trans.keyIndex         = keyIndex;
        trans.msgIn            = (uint32_t *) ecbExample.clearText;
        trans.msgOut           = (uint32_t *) ecbExample.msgOut;
        // Encrypt the plaintext with AES ECB
        status = CryptoCC26XX_transact(handle, (CryptoCC26XX_Transaction *) &trans);
        if(status != CRYPTOCC26XX_STATUS_SUCCESS){
                System_abort("Encryption failed.");
        }
        CryptoCC26XX_releaseKey(handle, &keyIndex);

        //printf("ClearText - %d, %d, %d, %d\n", ecbExample.clearText[0], ecbExample.clearText[1], ecbExample.clearText[2], ecbExample.clearText[3]);
        //printf("EncryptedText - %d, %d, %d, %d\n", ecbExample.msgOut[0], ecbExample.msgOut[1], ecbExample.msgOut[2], ecbExample.msgOut[3]);

        /* Create packet with incrementing sequence number and random payload */
        //packet[0] = (uint8_t)(seqNumber >> 8);
        //packet[1] = (uint8_t)(seqNumber++);

        //packet[0] = (uint8_t)(ecbExample.msgOut[0]);
        packet[1] = (uint8_t)(ecbExample.msgOut[1]);

        adc = ADC_open(Board_ADC, &params);
        if (adc != NULL) {
            ADC_close(adc);
        }

        int_fast16_t res;

        res = ADC_convert(adc, &adcValue);
        if (res == ADC_STATUS_SUCCESS) {
            uvAdcValue = ADC_convertRawToMicroVolts(adc, adcValue);
            //printf("ADC raw value = %d; ADC microvolts value = %d\n", packet[0], uvAdcValue);
        }

        ADC_close(adc);

        packet[0] = (uint8_t)(uvAdcValue/10000);

        uint8_t i;
        for (i = 2; i < PAYLOAD_LENGTH; i++)
        {
            packet[i] = rand();
        }


        /* Set absolute TX time to utilize automatic power management */
        curtime += PACKET_INTERVAL;
        RF_cmdPropTx.startTime = curtime;

        /* Send packet */
        RF_EventMask result = RF_runCmd(rfHandle, (RF_Op*)&RF_cmdPropTx, RF_PriorityNormal, NULL, 0);
        if (!(result & RF_EventLastCmdDone))
        {
            /* Error */
            while(1);
        }

        PIN_setOutputValue(pinHandle, Board_PIN_LED1,!PIN_getOutputValue(Board_PIN_LED1));
    }
}

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call driver init functions. */
    Board_initGeneral();
    ADC_init();
    CryptoCC26XX_init();

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, pinTable);
    if(!ledPinHandle)
    {
        System_abort("Error initializing board LED pins\n");
    }

    /* Initialize task */
    TxTask_init(ledPinHandle);

    /* Start BIOS */
    BIOS_start();

    return (0);
}
