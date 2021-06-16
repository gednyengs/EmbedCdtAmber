#include "amberm3vx_hal_ptfmctrl.h"

#if !defined (HSE_VALUE)
  #define HSE_VALUE     50000000
#endif

HAL_Status_e HAL_PtfmCtrl_Initialize(HAL_PtfmCtrl_t * PtfmCtrlPtr)
{
  assert_param(PtfmCtrlPtr != NULL);

  PtfmCtrlPtr->RegDefPtr = Device_PTFMCTRL;
  PtfmCtrlPtr->IsReady = TRUE;

  return HAL_OK;
}

HAL_Status_e HAL_PtfmCtrl_ReqReset(HAL_PtfmCtrl_t *PtfmCtrlPtr, u32 Mask)
{
  assert_param(PtfmCtrlPtr != NULL);
  assert_param(PtfmCtrlPtr->IsReady);
  assert_param(PtfmCtrlPtr->RegDefPtr != NULL);

  PtfmCtrl_RegDef_t *RegDefPtr = PtfmCtrlPtr->RegDefPtr;

  RegDefPtr->RESET_REQ |= Mask;
  while ((RegDefPtr->RESET_ACK & Mask) != Mask);
  return HAL_OK;
}

HAL_Status_e HAL_PtfmCtrl_ClearReset(HAL_PtfmCtrl_t *PtfmCtrlPtr, u32 Mask)
{
  assert_param(PtfmCtrlPtr != NULL);
  assert_param(PtfmCtrlPtr->IsReady);
  assert_param(PtfmCtrlPtr->RegDefPtr != NULL);

  PtfmCtrl_RegDef_t *RegDefPtr = PtfmCtrlPtr->RegDefPtr;

  u32 ClrMask = ~Mask;
  RegDefPtr->RESET_REQ &= ClrMask;
  while ((RegDefPtr->RESET_ACK & Mask) != 0);

  return HAL_OK;
}

HAL_Status_e HAL_PtfmCtrl_EnableCG(HAL_PtfmCtrl_t *PtfmCtrlPtr, u32 Mask)
{
  assert_param(PtfmCtrlPtr != NULL);
  assert_param(PtfmCtrlPtr->IsReady);
  assert_param(PtfmCtrlPtr->RegDefPtr != NULL);

  PtfmCtrl_RegDef_t *RegDefPtr = PtfmCtrlPtr->RegDefPtr;

  RegDefPtr->CLK_GATE_EN |= Mask;

  return HAL_OK;
}

HAL_Status_e HAL_PtfmCtrl_DisableCG(HAL_PtfmCtrl_t *PtfmCtrlPtr, u32 Mask)
{
  assert_param(PtfmCtrlPtr != NULL);
  assert_param(PtfmCtrlPtr->IsReady);
  assert_param(PtfmCtrlPtr->RegDefPtr != NULL);

  PtfmCtrl_RegDef_t *RegDefPtr = PtfmCtrlPtr->RegDefPtr;

  RegDefPtr->CLK_GATE_EN &= ~Mask;

  return HAL_OK;
}

HAL_Status_e HAL_PtfmCtrl_SelectClock(HAL_PtfmCtrl_t *PtfmCtrlPtr,
                                             u32 Mask,
                                             u32 Value)
{
  assert_param(PtfmCtrlPtr != NULL);
  assert_param(PtfmCtrlPtr->IsReady);
  assert_param(PtfmCtrlPtr->RegDefPtr != NULL);

  PtfmCtrl_RegDef_t *RegDefPtr = PtfmCtrlPtr->RegDefPtr;
  u32 CuratedVal = Value & 0x07;

  if (Mask & (1 << PTFMCTRL_SYS_Pos)) {
    RegDefPtr->SYS_CLK_SELECT = CuratedVal;
    SystemCoreClock = HSE_VALUE >> Value;
  }

  if (Mask & (1 << PTFMCTRL_DMA0_Pos))
    RegDefPtr->DMA0_PCLK_SELECT = CuratedVal;
  if (Mask & (1 << PTFMCTRL_DMA1_Pos))
    RegDefPtr->DMA1_PCLK_SELECT = CuratedVal;
  if (Mask & (1 << PTFMCTRL_TLX_FWD_Pos))
    RegDefPtr->TLX_FWD_CLK_SELECT = CuratedVal;
  if (Mask & (1 << PTFMCTRL_CGRA_Pos))
    RegDefPtr->CGRA_CLK_SELECT = CuratedVal;
  if (Mask & (1 << PTFMCTRL_TIMER0_Pos))
    RegDefPtr->TIMER0_CLK_SELECT = CuratedVal;
  if (Mask & (1 << PTFMCTRL_TIMER1_Pos))
    RegDefPtr->TIMER1_CLK_SELECT = CuratedVal;
  if (Mask & (1 << PTFMCTRL_UART0_Pos))
    RegDefPtr->UART0_CLK_SELECT = CuratedVal;
  if (Mask & (1 << PTFMCTRL_UART1_Pos))
    RegDefPtr->UART1_CLK_SELECT = CuratedVal;
  if (Mask & (1 << PTFMCTRL_WDOG_Pos))
    RegDefPtr->WDOG_CLK_SELECT = CuratedVal;

  return HAL_OK;
}
