#ifndef AMBERM3VX_HAL_PTFMCTRL_H
#define AMBERM3VX_HAL_PTFMCTRL_H

#ifdef __cplusplus
 extern "C" {
#endif

/************************* Includes *******************************************/
#include "amberm3vx.h"
#include "amberm3vx_hal_def.h"

/************************* Type Definitions ***********************************/

/**
 * HAL Platform Controller Driver Instance Data
 */
typedef struct {
  PtfmCtrl_RegDef_t *RegDefPtr;     /**< Pointer to register description      */
  u32 IsReady;                      /**< Device is ready                      */
} HAL_PtfmCtrl_t;

/************************* Function Prototypes ********************************/

/**
 * Initialize Platform Controller Driver
 * @param PtfmCtrlPtr  Pointer to user-allocated driver struct to initialize
 *
 * @return HAL_OK   on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_PtfmCtrl_Initialize(HAL_PtfmCtrl_t * PtfmCtrlPtr);

/**
 * Request a Peripheral Reset
 * @param PtfmCtrlPtr Pointer to Platform Controller driver struct
 * @param Mask  OR-mask of all device positions to reset
 *
 * @return HAL_OK on success, otherise HAL_ERROR
 */
extern HAL_Status_e HAL_PtfmCtrl_ReqReset(HAL_PtfmCtrl_t *PtfmCtrlPtr, u32 Mask);

/**
 * Clear Peripheral Resets
 * @param PtfmCtrlPtr Pointer to Platform Controller driver struct
 * @param Mask  OR-mask of all device positions to clear reset
 *
 * @return HAL_OK on success, otherise HAL_ERROR
 */
extern HAL_Status_e HAL_PtfmCtrl_ClearReset(HAL_PtfmCtrl_t *PtfmCtrlPtr, u32 Mask);

/**
 * Enable Peripheral Clock Gating
 * @param PtfmCtrlPtr Pointer to Platform Controller driver struct
 * @param Mask  OR-mask of all device positions to clock gate
 *
 * @return HAL_OK on success, otherise HAL_ERROR
 */
extern HAL_Status_e HAL_PtfmCtrl_EnableCG(HAL_PtfmCtrl_t *PtfmCtrlPtr, u32 Mask);

/**
 * Disable Peripheral Clock Gating
 * @param PtfmCtrlPtr Pointer to Platform Controller driver struct
 * @param Mask  OR-mask of all device positions to disable clock gate for
 *
 * @return HAL_OK on success, otherise HAL_ERROR
 */
extern HAL_Status_e HAL_PtfmCtrl_DisableCG(HAL_PtfmCtrl_t *PtfmCtrlPtr, u32 Mask);

/**
 * Select Divided Clock for Peripherals
 * @param PtfmCtrlPtr Pointer to Platform Controller driver struct
 * @param Mask  OR-mask of all device positions to attribute the clock
 * @param Value The clock select value
 *
 * @return HAL_OK on success, otherise HAL_ERROR
 */
extern HAL_Status_e HAL_PtfmCtrl_SelectClock(HAL_PtfmCtrl_t *PtfmCtrlPtr,
                                             u32 Mask,
                                             u32 Value);


#ifdef __cplusplus
}
#endif

#endif /* AMBERM3VX_HAL_PTFMCTRL_H */
