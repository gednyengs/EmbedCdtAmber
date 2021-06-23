/************************* Includes  ******************************************/
#include "amberm3vx_hal_uart.h"

/************************* Variable Declarations ******************************/

static HAL_Uart_t *UartInstances[2] = {NULL, NULL};

/************************* Function Definitions *******************************/

HAL_Status_e HAL_Uart_Initialize(HAL_Uart_t * UartPtr, u8 UartID)
{
  HAL_Status_e Status;

  assert_param(UartPtr != NULL);
  assert_param(UartID < 2);

  if (UartID == HAL_UART_0) {
    UartPtr->RegDefPtr = Device_UART0;
  } else {
    UartPtr->RegDefPtr = Device_UART1;
  }

  UartPtr->IsReady = 1;

  Status = HAL_Uart_ClearStats(UartPtr);
  if (Status != HAL_OK) {
    UartPtr->IsReady = 0;
    return Status;
  }

  UartPtr->RxBuf.BufPtr = NULL;
  UartPtr->RxBuf.NumRemBytes = 0;
  UartPtr->RxBuf.NumReqBytes = 0;

  UartPtr->TxBuf.BufPtr = NULL;
  UartPtr->TxBuf.NumRemBytes = 0;
  UartPtr->TxBuf.NumReqBytes = 0;

  UartPtr->RxCallBack = NULL;
  UartPtr->RxCallBackRef = NULL;

  UartPtr->TxCallBack = NULL;
  UartPtr->TxCallBackRef = NULL;

  UartInstances[UartID] = UartPtr;

  return HAL_OK;
}

HAL_Status_e HAL_Uart_SetBaudRate(HAL_Uart_t *UartPtr, u32 BaudDiv)
{
  assert_param(UartPtr != NULL);
  assert_param(UartPtr->IsReady == 1);
  assert_param(UartPtr->RegDefPtr != NULL);

  u32 UartCtrl = UartPtr->RegDefPtr->CTRL;

  /* Disable UART when changing configuration */
  UartPtr->RegDefPtr->CTRL = UartCtrl & ~((1 << UART_CTRL_TXEN_Pos) |
                                (1 << UART_CTRL_RXEN_Pos));
  /* Change baudrate */
  UartPtr->RegDefPtr->BAUDDIV = BaudDiv;
  /* Set configuration back */
  UartPtr->RegDefPtr->CTRL = UartCtrl;

  return HAL_OK;

}

HAL_Status_e HAL_Uart_Send(HAL_Uart_t *UartPtr, u8 *BufPtr, u32 Len)
{
  assert_param(UartPtr != NULL);
  assert_param(UartPtr->RegDefPtr != NULL);
  assert_param(BufPtr != NULL);
  assert_param(Len > 0);

  /* 0 = Polled mode, 1 = Interrupt mode */
  u8 UartMode;

  if (!UartPtr->IsReady)
    return HAL_BUSY;

  /* Enable TX */
  UartPtr->RegDefPtr->CTRL |= UART_CTRL_TXEN_Msk;

  UartMode = !!(UartPtr->RegDefPtr->CTRL & UART_CTRL_RXIRQEN_Msk);

  UartPtr->IsReady = 0;

  if (UartMode == 0) {
    UartPtr->TxBuf.BufPtr = NULL;
    UartPtr->TxBuf.NumReqBytes = 0;
    UartPtr->TxBuf.NumRemBytes = 0;
    u8 *bf = BufPtr;

    while (bf < (BufPtr + Len)) {
      while(UartPtr->RegDefPtr->STATE & UART_STATE_TXBF_Msk);
      UartPtr->RegDefPtr->DATA = (u32) *bf;
      bf++;
      UartPtr->Stats.CharTransmitted++;
    }

    UartPtr->IsReady = 1;
  } else {
    return HAL_ERROR; // no support for interrupt mode yet
  }

  return HAL_OK;
}

HAL_Status_e HAL_Uart_Recv(HAL_Uart_t *UartPtr, u8 *BufPtr, u32 Len)
{
  assert_param(UartPtr != NULL);
  assert_param(UartPtr->RegDefPtr != NULL);
  assert_param(BufPtr != NULL);
  assert_param(Len > 0);

  /* 0 = Polled mode, 1 = Interrupt mode */
  u8 UartMode;

  if (!UartPtr->IsReady)
    return HAL_BUSY;

  /* Enable RX */
  UartPtr->RegDefPtr->CTRL |= UART_CTRL_RXEN_Msk;

  UartMode = !!(UartPtr->RegDefPtr->CTRL & UART_CTRL_RXIRQEN_Msk);

  UartPtr->IsReady = 0;

  if (UartMode == 0) {
    UartPtr->RxBuf.BufPtr = NULL;
    UartPtr->RxBuf.NumReqBytes = 0;
    UartPtr->RxBuf.NumRemBytes = 0;
    u8 *bf = BufPtr;

    while (bf < (BufPtr + Len)) {
      while(!(UartPtr->RegDefPtr->STATE & UART_STATE_RXBF_Msk));
      *bf++ = (u8) UartPtr->RegDefPtr->DATA;
      UartPtr->Stats.CharReceived++;
    }

    UartPtr->IsReady = 1;
  } else {
    return HAL_ERROR; // No support for interrupt mode yet
  }

  return HAL_OK;
}

HAL_Status_e HAL_Uart_EnableInterrupt(HAL_Uart_t *UartPtr)
{
  HAL_UNUSED(UartPtr);
  return HAL_ERROR; // not implemented yet
}

HAL_Status_e HAL_Uart_DisableInterrupt(HAL_Uart_t * UartPtr)
{
  HAL_UNUSED(UartPtr);
  return HAL_ERROR; // not implemented yet
}

HAL_Status_e HAL_Uart_SetRxCallback(HAL_Uart_t *UartPtr,
                                           HAL_Uart_CallBackFn FuncPtr)
{
  HAL_UNUSED(UartPtr);
  HAL_UNUSED(FuncPtr);
  return HAL_ERROR; // not implemented yet
}

HAL_Status_e HAL_Uart_SetTxCallback(HAL_Uart_t *UartPtr,
                                           HAL_Uart_CallBackFn FuncPtr)
{
  HAL_UNUSED(UartPtr);
  HAL_UNUSED(FuncPtr);
  return HAL_ERROR; // not implemented yet
}

HAL_Status_e HAL_Uart_ClearStats(HAL_Uart_t *UartPtr)
{
  assert_param(UartPtr != NULL);
  assert_param(UartPtr->IsReady);

  UartPtr->Stats.TxInterrupts = 0;
  UartPtr->Stats.RxInterrupts = 0;
  UartPtr->Stats.CharTransmitted = 0;
  UartPtr->Stats.CharReceived = 0;
  UartPtr->Stats.RxOverrunErrors = 0;

  return HAL_OK;
}

void UART_IRQHandler(void)
{

}
