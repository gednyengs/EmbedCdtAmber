/**
  ******************************************************************************
  * @file    amberm3xx.h
  * @brief   CMSIS AMBERM3xx Device Peripheral Access Layer Header File.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The AMBERM3xx device used in the target application
  *              - To use or not the peripheral�s drivers in application code(i.e.
  *                code will be based on direct access to peripheral�s registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_HAL_DRIVER"
  *
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup amberm3xx
  * @{
  */

#ifndef __AMBERM3xx_H
#define __AMBERM3xx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief AMBER Family
  */
#if !defined (AMBER)
#define AMBER
#endif /* AMBER */

/* Uncomment the line below according to the target AMBER device used in your
   application
  */
#if !defined (AMBERM301xx)
  //#define AMBERM301xx
#endif

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
#if !defined  (USE_HAL_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
  /*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

/**
  * @brief CMSIS Device version number V2.2.4
  */
#define __AMBERM3xx_CMSIS_VERSION_MAIN   (0x02U) /*!< [31:24] main version */
#define __AMBERM3xx_CMSIS_VERSION_SUB1   (0x02U) /*!< [23:16] sub1 version */
#define __AMBERM3xx_CMSIS_VERSION_SUB2   (0x04U) /*!< [15:8]  sub2 version */
#define __AMBERM3xx_CMSIS_VERSION_RC     (0x00U) /*!< [7:0]  release candidate */
#define __AMBERM3xx_CMSIS_VERSION        ((__AMBERM3xx_CMSIS_VERSION_MAIN << 24)\
                                         |(__AMBERM3xx_CMSIS_VERSION_SUB1 << 16)\
                                         |(__AMBERM3xx_CMSIS_VERSION_SUB2 << 8 )\
                                         |(__AMBERM3xx_CMSIS_VERSION))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(AMBERM301xx)
  #include "amberm301xx.h"
 #error "Please select first the target AMBERM3xx device used in your application (in amberm3xx.h file)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */
typedef enum
{
  RESET = 0U,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0U,
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;

/**
  * @}
  */


/** @addtogroup Exported_macro
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))


/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "amberm3xx_hal.h"
#endif /* USE_HAL_DRIVER */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AMBERM3xx_H */

/**
  * @}
  */

/**
  * @}
  */




/************************ (C) COPYRIGHT Stanford AHA *****END OF FILE****/
