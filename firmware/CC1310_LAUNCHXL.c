/*
 * Copyright (c) 2015-2017, Texas Instruments Incorporated
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

/*
 *  ====================== CC1310_LAUNCHXL.c ===================================
 *  This file is responsible for setting up the board specific items for the
 *  CC1310_LAUNCHXL board.
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>

#include <ti/devices/cc13x0/driverlib/ioc.h>
#include <ti/devices/cc13x0/driverlib/udma.h>
#include <ti/devices/cc13x0/inc/hw_ints.h>
#include <ti/devices/cc13x0/inc/hw_memmap.h>

#include "CC1310_LAUNCHXL.h"
/*
 *  =============================== ADC ===============================
 */
#include <ti/drivers/ADC.h>
#include <ti/drivers/adc/ADCCC26XX.h>

ADCCC26XX_Object adcCC26xxObjects[CC1310_LAUNCHXL_ADCCOUNT];


const ADCCC26XX_HWAttrs adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADCCOUNT] = {
                                                                      {
                                                                          .adcDIO              = CC1310_LAUNCHXL_DIO23_ANALOG,
                                                                          .adcCompBInput       = ADC_COMPB_IN_AUXIO7,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,
                                                                      },
                                                                      {
                                                                          .adcDIO              = CC1310_LAUNCHXL_DIO24_ANALOG,
                                                                          .adcCompBInput       = ADC_COMPB_IN_AUXIO6,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,

                                                                      },
                                                                      {
                                                                          .adcDIO              = CC1310_LAUNCHXL_DIO25_ANALOG,
                                                                          .adcCompBInput       = ADC_COMPB_IN_AUXIO5,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,

                                                                      },
                                                                      {
                                                                          .adcDIO              = CC1310_LAUNCHXL_DIO26_ANALOG,
                                                                          .adcCompBInput       = ADC_COMPB_IN_AUXIO4,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,

                                                                      },
                                                                      {
                                                                          .adcDIO              = CC1310_LAUNCHXL_DIO27_ANALOG,
                                                                          .adcCompBInput       = ADC_COMPB_IN_AUXIO3,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,

                                                                      },
                                                                      {
                                                                          .adcDIO              = CC1310_LAUNCHXL_DIO28_ANALOG,
                                                                          .adcCompBInput       = ADC_COMPB_IN_AUXIO2,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,

                                                                      },
                                                                      {
                                                                          .adcDIO              = CC1310_LAUNCHXL_DIO29_ANALOG,
                                                                          .adcCompBInput       = ADC_COMPB_IN_AUXIO1,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,

                                                                      },
                                                                      {
                                                                          .adcDIO              = CC1310_LAUNCHXL_DIO30_ANALOG,
                                                                          .adcCompBInput       = ADC_COMPB_IN_AUXIO0,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_10P9_MS,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,

                                                                      },
                                                                      {
                                                                          .adcDIO              = PIN_UNASSIGNED,
                                                                          .adcCompBInput       = ADC_COMPB_IN_DCOUPL,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,

                                                                      },
                                                                      {
                                                                          .adcDIO              = PIN_UNASSIGNED,
                                                                          .adcCompBInput       = ADC_COMPB_IN_VSS,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,

                                                                      },
                                                                      {
                                                                          .adcDIO              = PIN_UNASSIGNED,
                                                                          .adcCompBInput       = ADC_COMPB_IN_VDDS,
                                                                          .refSource           = ADCCC26XX_FIXED_REFERENCE,
                                                                          .samplingDuration    = ADCCC26XX_SAMPLING_DURATION_2P7_US,
                                                                          .inputScalingEnabled = true,
                                                                          .triggerSource       = ADCCC26XX_TRIGGER_MANUAL,

                                                                      }
};

const ADC_Config ADC_config[CC1310_LAUNCHXL_ADCCOUNT] = {
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADC0], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADC0]},
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADC1], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADC1]},
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADC2], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADC2]},
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADC3], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADC3]},
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADC4], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADC4]},
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADC5], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADC5]},
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADC6], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADC6]},
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADC7], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADC7]},
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADCDCOUPL], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADCDCOUPL]},
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADCVSS], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADCVSS]},
                                                         {&ADCCC26XX_fxnTable, &adcCC26xxObjects[CC1310_LAUNCHXL_ADCVDDS], &adcCC26xxHWAttrs[CC1310_LAUNCHXL_ADCVDDS]},
};

const uint_least8_t ADC_count = CC1310_LAUNCHXL_ADCCOUNT;

/*
 *  =============================== Crypto ===============================
 */
#include <ti/drivers/crypto/CryptoCC26XX.h>

CryptoCC26XX_Object cryptoCC26XXObjects[CC1310_LAUNCHXL_CRYPTOCOUNT];

const CryptoCC26XX_HWAttrs cryptoCC26XXHWAttrs[CC1310_LAUNCHXL_CRYPTOCOUNT] = {
    {
        .baseAddr       = CRYPTO_BASE,
        .powerMngrId    = PowerCC26XX_PERIPH_CRYPTO,
        .intNum         = INT_CRYPTO_RESULT_AVAIL_IRQ,
        .intPriority    = ~0,
    }
};

const CryptoCC26XX_Config CryptoCC26XX_config[CC1310_LAUNCHXL_CRYPTOCOUNT] = {
    {
         .object  = &cryptoCC26XXObjects[CC1310_LAUNCHXL_CRYPTO0],
         .hwAttrs = &cryptoCC26XXHWAttrs[CC1310_LAUNCHXL_CRYPTO0]
    }
};
/*
 *  =============================== GPIO ===============================
 */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/gpio/GPIOCC26XX.h>

/*
 * Array of Pin configurations
 * NOTE: The order of the pin configurations must coincide with what was
 *       defined in CC1310_LAUNCHXL.h
 * NOTE: Pins not used for interrupts should be placed at the end of the
 *       array. Callback entries can be omitted from callbacks array to
 *       reduce memory usage.
 */
GPIO_PinConfig gpioPinConfigs[] = {
    /* Input pins */
    GPIOCC26XX_DIO_13 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING,  /* Button 0 */
    GPIOCC26XX_DIO_14 | GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_RISING,  /* Button 1 */

    /* Output pins */
    GPIOCC26XX_DIO_07 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,  /* Green LED */
    GPIOCC26XX_DIO_06 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_STR_HIGH | GPIO_CFG_OUT_LOW,  /* Red LED */
};

/*
 * Array of callback function pointers
 * NOTE: The order of the pin configurations must coincide with what was
 *       defined in CC1310_LAUNCH.h
 * NOTE: Pins not used for interrupts can be omitted from callbacks array to
 *       reduce memory usage (if placed at end of gpioPinConfigs array).
 */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    NULL,  /* Button 0 */
    NULL,  /* Button 1 */
};

const GPIOCC26XX_Config GPIOCC26XX_config = {
    .pinConfigs = (GPIO_PinConfig *)gpioPinConfigs,
    .callbacks = (GPIO_CallbackFxn *)gpioCallbackFunctions,
    .numberOfPinConfigs = CC1310_LAUNCHXL_GPIOCOUNT,
    .numberOfCallbacks  = sizeof(gpioCallbackFunctions)/sizeof(GPIO_CallbackFxn),
    .intPriority = (~0)
};

/*
 *  =============================== PIN ===============================
 */
#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>

const PIN_Config BoardGpioInitTable[] = {

    CC1310_LAUNCHXL_PIN_GLED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,       /* LED initially off          */

    PIN_TERMINATE
};

const PINCC26XX_HWAttrs PINCC26XX_hwAttrs = {
    .intPriority = ~0,
    .swiPriority = 0
};
/*
 *  =============================== Power ===============================
 */
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>

const PowerCC26XX_Config PowerCC26XX_config = {
    .policyInitFxn      = NULL,
    .policyFxn          = &PowerCC26XX_standbyPolicy,
    .calibrateFxn       = &PowerCC26XX_calibrate,
    .enablePolicy       = TRUE,
    .calibrateRCOSC_LF  = TRUE,
    .calibrateRCOSC_HF  = TRUE,
};

/*
 *  =============================== RF Driver ===============================
 */
#include <ti/drivers/rf/RF.h>

const RFCC26XX_HWAttrs RFCC26XX_hwAttrs = {
    .hwiCpe0Priority = ~0,
    .hwiHwPriority   = ~0,
    .swiCpe0Priority =  0,
    .swiHwPriority   =  0,
};
/*
 *  ======== CC1310_LAUNCHXL_initGeneral ========
 */
void CC1310_LAUNCHXL_initGeneral(void)
{
    Power_init();

    if (PIN_init(BoardGpioInitTable) != PIN_SUCCESS) {
        System_abort("Error with PIN_init\n");
    }
}
