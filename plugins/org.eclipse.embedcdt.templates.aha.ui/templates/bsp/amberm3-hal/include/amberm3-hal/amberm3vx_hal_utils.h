#ifndef AMBERM3VX_HAL_UTILS_H
#define AMBERM3VX_HAL_UTILS_H

#ifdef __cplusplus
 extern "C" {
#endif

/************************* Includes *******************************************/
#include "amberm3vx.h"
#include "amberm3vx_hal_def.h"

/************************* Type Definitions ***********************************/

/************************* Function Prototypes ********************************/

/**
 * Delay in Milliseconds
 * @param MilliSeconds The number of milliseconds to delay
 *
 * @return None
 */
extern void HAL_Delay(u32 MilliSeconds);

#ifdef __cplusplus
}
#endif

#endif /* AMBERM3VX_HAL_UTILS_H */
