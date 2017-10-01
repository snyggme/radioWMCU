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
/** ============================================================================
 *  @file       CC1310_LAUNCHXL.h
 *
 *  @brief      CC1310 LaunchPad Board Specific header file.
 *
 *  The CC1310_LAUNCHXL header file should be included in an application as
 *  follows:
 *  @code
 *  #include "CC1310_LAUNCHXL.h"
 *  @endcode
 *
 *  ============================================================================
 */
#ifndef __CC1310_LAUNCHXL_BOARD_H__
#define __CC1310_LAUNCHXL_BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <ti/drivers/PIN.h>
#include <ti/devices/cc13x0/driverlib/ioc.h>

/* Externs */
extern const PIN_Config BoardGpioInitTable[];

/* Defines */
#define CC1310_LAUNCHXL

#define CC1310_LAUNCHXL_DIO23_ANALOG          IOID_23
#define CC1310_LAUNCHXL_DIO24_ANALOG          IOID_24
#define CC1310_LAUNCHXL_DIO25_ANALOG          IOID_25
#define CC1310_LAUNCHXL_DIO26_ANALOG          IOID_26
#define CC1310_LAUNCHXL_DIO27_ANALOG          IOID_27
#define CC1310_LAUNCHXL_DIO28_ANALOG          IOID_28
#define CC1310_LAUNCHXL_DIO29_ANALOG          IOID_29
#define CC1310_LAUNCHXL_DIO30_ANALOG          IOID_30

#define CC1310_LAUNCHXL_PIN_GLED              IOID_12

/*!
 *  @brief  Initialize the general board specific settings
 *
 *  This function initializes the general board specific settings.
 */
void CC1310_LAUNCHXL_initGeneral(void);

/*!
 *  @def    CC1310_LAUNCHXL_ADCName
 *  @brief  Enum of ADCs
 */
typedef enum CC1310_LAUNCHXL_ADCName {
    CC1310_LAUNCHXL_ADC0 = 0,
    CC1310_LAUNCHXL_ADC1,
    CC1310_LAUNCHXL_ADC2,
    CC1310_LAUNCHXL_ADC3,
    CC1310_LAUNCHXL_ADC4,
    CC1310_LAUNCHXL_ADC5,
    CC1310_LAUNCHXL_ADC6,
    CC1310_LAUNCHXL_ADC7,
    CC1310_LAUNCHXL_ADCDCOUPL,
    CC1310_LAUNCHXL_ADCVSS,
    CC1310_LAUNCHXL_ADCVDDS,

    CC1310_LAUNCHXL_ADCCOUNT
} CC1310_LAUNCHXL_ADCName;
/*!
 *  @def    CC1310_LAUNCHXL_CryptoName
 *  @brief  Enum of Crypto names
 */
typedef enum CC1310_LAUNCHXL_CryptoName {
    CC1310_LAUNCHXL_CRYPTO0 = 0,

    CC1310_LAUNCHXL_CRYPTOCOUNT
} CC1310_LAUNCHXL_CryptoName;

/*!
 *  @def    CC1310_LAUNCHXL_GPIOName
 *  @brief  Enum of GPIO names
 */
typedef enum CC1310_LAUNCHXL_GPIOName {
    CC1310_LAUNCHXL_GPIO_S1 = 0,
    CC1310_LAUNCHXL_GPIO_S2,
    CC1310_LAUNCHXL_GPIO_LED_GREEN,
    CC1310_LAUNCHXL_GPIO_LED_RED,

    CC1310_LAUNCHXL_GPIOCOUNT
} CC1310_LAUNCHXL_GPIOName;

#ifdef __cplusplus
}
#endif

#endif /* __CC1310_LAUNCHXL_BOARD_H__ */
