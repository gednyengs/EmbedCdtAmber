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

typedef struct
{
  u32 Upper;
  u32 Lower;
} HAL_uint64_t;

/************************* Macro Definitions **********************************/

/**
 * Return the most significant word of the 64-bit double-word data type
 * @param   x is 64-bit double-word
 * @return  Upper word (32 bits) of the double-word
 */
#define HAL_UINT64_MSW(x) ((x).Upper)

/**
 * Return the least significant word of the 64-bit double-word data type
 * @param   x is 64-bit double-word
 * @return  Lower word (32 bits) of the double-word
 */
#define HAL_UINT64_LSW(x) ((x).Lower)

/* Use to suppress warning on unused variable */
#define HAL_UNUSED(X)                   (void)X

#define HAL_IS_BIT_SET(REG, BIT)        (((REG) & (BIT)) == (BIT))
#define HAL_IS_BIT_CLR(REG, BIT)        ((REG) & (BIT)) == 0U)

/************************* Function Defintions ********************************/

static __INLINE u32 HAL_In32(void *Addr)
{
  return *(volatile u32 *) Addr;
}

static __INLINE void HAL_Out32(void *Addr, u32 Data)
{
  volatile u32 *IOAddr = (volatile u32 *) Addr;
  *IOAddr = Data;
}

#ifdef __cplusplus
}
#endif

#endif /* AMBERM3VX_HAL_DEF_H */
