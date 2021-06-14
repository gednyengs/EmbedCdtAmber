#ifndef AMBERM3VX_HAL_TIMER_H
#define AMBERM3VX_HAL_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

/************************* Includes *******************************************/
#include "amberm3vx.h"
#include "amberm3vx_hal_def.h"

/************************* Type Definitions ***********************************/

/**
 * Signature for timer callback function
 */
typedef void (*HAL_Timer_CallBack_Fn)(void *CallBackRef);

/**
 * Timer Statistics
 */
typedef struct {
  u32 Interrupts;     /* Number of interrupts that have occurred */
} HAL_Timer_Stats_t;

/**
 * HAL Timer Driver Instance Data
 */
typedef struct {
  Timer_RegDef_t *RegDefPtr;        /**< Pointer to register description      */
  HAL_Timer_Stats_t Stats;          /**< Timer Statistics                     */
  u32 IsReady;                      /**< Device is ready                      */
  HAL_Timer_CallBack_Fn CallBack;   /**< Timer callback function              */
  void *CallBackRef;                /**< Callback reference cookie            */
} HAL_Timer_t;

/************************* Function Prototypes ********************************/

/**
 * Initialize Timer Driver
 * @param TimerPtr  Pointer to user-allocated driver struct to initialize
 * @param TimerID   ID of timer instance to initialize
 *                  0 = TIMER0
 *                  1 = TIMER1
 *
 * @return HAL_OK   on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Timer_Initialize(HAL_Timer_t * TimerPtr, u8 TimerID);

/** Set Timer for Multi-Shoot Mode
 * @param TimerPtr  Pointer to timer driver struct
 * @param Reload    The value to which the rimer is to be set after underflow
 * @param IrqEn     Specifies whether to enable timer interrupt or not
 *
 * @return          HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Timer_MultiShoot(HAL_Timer_t * TimerPtr, u32 Reload,
                                         u32 IrqEn);
/**
 * Get Timer's Reload Value
 * @param TimerPtr  Pointer to timer driver struct
 *
 * @return          Timer's reload value
 */
extern u32  HAL_Timer_GetReload(HAL_Timer_t *TimerPtr);

/**
 * Set Timer's Reload Value
 * @param TimerPtr  Pointer to timer driver struct
 * @param Value     Reload Value
 *
 * @return          HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Timer_SetReload(HAL_Timer_t *TimerPtr, u32 Value);

/**
 * Get Current Timer's Value
 * @param TimerPtr  Pointer to timer driver struct
 *
 * @return          Timer's current value
 */
extern u32  HAL_Timer_GetValue(HAL_Timer_t *TimerPtr);

/**
 * Set Timer's Current Value
 * @param TimerPtr  Pointer to timer driver struct
 * @param Value     Timer Value
 *
 * @return          HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Timer_SetValue(HAL_Timer_t *TimerPtr, u32 Value);

/**
 * Stop the Timer
 * @param TimerPtr  Pointer to timer driver struct
 *
 * @return          HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Timer_StopTimer(HAL_Timer_t *TimerPtr);

/**
 * Start the Timer
 * @param TimerPtr  Pointer to timer driver struct
 *
 * @return          HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Timer_StartTimer(HAL_Timer_t *TimerPtr);

/**
 * Clear Timer Interrupt
 * @param TimerPtr  Pointer to timer driver struct
 *
 * @return          HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Timer_ClearIRQ(HAL_Timer_t *TimerPtr);

/**
 * Get Timer IRQ Status
 * @param TimerPtr  Pointer to timer driver struct
 *
 * @return          Timer IRQ status
 */
extern u32  HAL_Timer_StatusIRQ(HAL_Timer_t *TimerPtr);

/**
 * Enable Timer Interrupt
 * @param TimerPtr  Pointer to timer driver struct
 *
 * @return          HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Timer_EnableIRQ(HAL_Timer_t *TimerPtr);

/**
 * Disable Timer Interrupt
 * @param TimerPtr  Pointer to timer driver struct
 *
 * @return          HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Timer_DisableIRQ(HAL_Timer_t *TimerPtr);

#ifdef __cplusplus
}
#endif

#endif /* AMBERM3VX_HAL_TIMER_H */
