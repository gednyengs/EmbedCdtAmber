#ifndef AMBERM3VX_H
#define AMBERM3VX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/**************************** Includes ****************************************/
#include <stdint.h>

/**************************** Defines *****************************************/
#if !defined (AMBER)
#define AMBER
#endif /* AMBER */

/**************************** Constant Definitions ****************************/

#ifndef TRUE
  #define TRUE    1U
#endif

#ifndef FALSE
  #define FALSE   0U
#endif

#ifndef NULL
  #define NULL    0U
#endif

/**************************** Type Definitions ********************************/
typedef enum
{
  SUCCESS = 0U,
  ERROR = 1U
} ErrorStatus_e;

typedef uint8_t         u8;
typedef uint16_t        u16;
typedef uint32_t        u32;
typedef uint64_t        u64;

typedef int8_t          s8;
typedef int16_t         s16;
typedef int32_t         s32;

/**************************** Includes ****************************************/

#if defined(AMBERM3V1)
  #include "amberm3v1.h"
#endif

#if defined (USE_HAL_DRIVER)
 #include "amberm3vx_hal.h"
#endif

#include "amber_assert.h"

/**************************** Macro Definitions *******************************/

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AMBERM3VX_H */
