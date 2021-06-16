/******************************************************************************
  * @file    amberm3vx_hal_def.h
  * @author  Gedeon Nyengele
  * @brief   This file contains HAL common defines, enumeration, macros, types,
  *             and structures definitions.
  *
  *****************************************************************************/

#ifndef AMBERM3VX_HAL_DEF_H
#define AMBERM3VX_HAL_DEF_H

#ifdef __cplusplus
 extern "C" {
#endif

/************************* Includes *******************************************/
#include "amberm3vx.h"
#include <stdint.h>

/************************* Constant Definitions *******************************/
#define HAL_MAX_DELAY   0xFFFFFFFFU

/************************* Type Definitions ***********************************/
typedef enum
{
  HAL_ERROR             = -1,
  HAL_OK                = 0x00,
  HAL_BUSY              = 0x01,
  HAL_TIMEOUT           = 0x02
} HAL_Status_e;

typedef enum
{
  HAL_UNLOCKED          = 0x00,
  HAL_LOCKED            = 0x01
} HAL_LockStatus_e;

typedef uint8_t         u8;
typedef uint16_t        u16;
typedef uint32_t        u32;
typedef int8_t          s8;
typedef int16_t         s16;
typedef int32_t         s32;

/************************* Macro Definitions **********************************/

/* Use to suppress warning on unused variable */
#define HAL_UNUSED(X)                   (void)X

#define HAL_IS_BIT_SET(REG, BIT)        (((REG) & (BIT)) == (BIT))
#define HAL_IS_BIT_CLR(REG, BIT)        ((REG) & (BIT)) == 0U)

#ifdef __cplusplus
}
#endif

#endif /* AMBERM3VX_HAL_DEF_H */
