/**
  ******************************************************************************
  * @file    system_amberm3xx.h
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M3 Device System Source File for AMBERM3xx devices.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup amberm3xx_system
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_AMBERM3XX_H
#define __SYSTEM_AMBERM3XX_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup AMBERM3xx_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup AMBERM3xx_System_Exported_types
  * @{
  */
  /* This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
         Note: If you use this function to configure the system clock; then there
               is no need to call the 2 first functions listed above, since SystemCoreClock
               variable is updated automatically.
  */
extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

extern const uint8_t  AHBPrescTable[16];    /*!< AHB prescalers table values */
extern const uint8_t  APBPrescTable[8];     /*!< APB prescalers table values */

/**
  * @}
  */

/** @addtogroup AMBERM3xx_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup AMBERM3xx_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup AMBERM3xx_System_Exported_Functions
  * @{
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_AMBERM3XX_H */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT Stanford AHA *****END OF FILE****/
