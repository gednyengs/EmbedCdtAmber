/**************************************************************************//**
* @file     system_amberm3vx.c
* @brief    CMSIS Device System Source File for AMBERM3Vx Device Family
* @version  V5.3.1
******************************************************************************/
/*
* Copyright (c) 2009-2018 Arm Limited. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <stdint.h>
#include "cmsis_device.h"

/*----------------------------------------------------------------------------
 Define clocks
*----------------------------------------------------------------------------*/
#if !defined (HSE_VALUE)
  #define HSE_VALUE     50000000
#endif

/*----------------------------------------------------------------------------
 ISR Vector Start Address
*----------------------------------------------------------------------------*/
extern unsigned int __vectors_start;

/*----------------------------------------------------------------------------
 System Core Clock Variable
*----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = (HSE_VALUE >> 1);  /* System Core Clock Frequency */

/*----------------------------------------------------------------------------
 System Core Clock update function
*----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)
{
  uint32_t SysClkDiv = Device_PTFMCTRL->SYS_CLK_SELECT;
  SystemCoreClock = HSE_VALUE  >> SysClkDiv;
}

/*----------------------------------------------------------------------------
 System initialization function
*----------------------------------------------------------------------------*/
void SystemInit (void)
{

#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
 SCB->VTOR = (uint32_t)(&__vectors_start);
#endif

#ifdef UNALIGNED_SUPPORT_DISABLE
 SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif

#if defined(OS_DEBUG_SEMIHOSTING_FAULTS)
  SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;
#endif

 SystemCoreClockUpdate();
}
