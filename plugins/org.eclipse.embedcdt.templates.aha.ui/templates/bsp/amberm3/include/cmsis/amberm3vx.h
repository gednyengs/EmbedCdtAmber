#ifndef AMBERM3VX_H
#define AMBERM3VX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/**************************** Defines *****************************************/
#if !defined (AMBER)
#define AMBER
#endif /* AMBER */

/**************************** Type Definitions ********************************/
typedef enum
{
  SUCCESS = 0U,
  ERROR = 1U
} ErrorStatus_e;

/**************************** Includes ****************************************/

#if defined(AMBERM3V1)
  #include "amberm3v1.h"
#endif

#if defined (USE_HAL_DRIVER)
 #include "amberm3vx_hal.h"
#endif

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
