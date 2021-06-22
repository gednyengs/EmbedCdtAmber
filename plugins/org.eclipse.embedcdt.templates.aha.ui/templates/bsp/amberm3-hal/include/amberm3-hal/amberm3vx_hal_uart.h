#ifndef AMBERM3VX_HAL_UART_H
#define AMBERM3VX_HAL_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/************************* Includes *******************************************/
#include "amberm3vx.h"
#include "amberm3vx_hal_def.h"

/************************* Constant Definitions *******************************/

#define HAL_UART_0    0
#define HAL_UART_1    1

/************************* Type Definitions ***********************************/

/**
 * Signature for UART callback function
 */
typedef void (*HAL_Uart_CallBackFn)(void *CallBackRef);

/**
 * UART Statistics
 */
typedef struct {
  u32 TxInterrupts;       /**< Number of transmit interrupts */
  u32 RxInterrupts;       /**< Number of receive interrupts */
  u32 CharTransmitted;    /**< Number of characters transmitted */
  u32 CharReceived;       /**< Number of characters received */
  u32 RxOverrunErrors;    /**< Number of receive overruns */
} HAL_Uart_Stats_t;

/**
 * Rx/Tx Buffer
 */
typedef struct {
  u8 *BufPtr;
  u32 NumReqBytes;
  u32 NumRemBytes;
} HAL_Uart_Buffer_t;

/**
 * HAL UART Driver Instance Data
 */
typedef struct {
  Uart_RegDef_t *RegDefPtr;         /**< Pointer to register description      */
  HAL_Uart_Stats_t Stats;           /**< UART Statistics                      */
  volatile u32 IsReady;             /**< Device is ready                      */

  HAL_Uart_Buffer_t RxBuf;
  HAL_Uart_Buffer_t TxBuf;

  HAL_Uart_CallBackFn RxCallBack;   /**< Rx callback function                 */
  void *RxCallBackRef;              /**< Rx Callback reference cookie         */
  HAL_Uart_CallBackFn TxCallBack;   /**< Rx callback function                 */
  void *TxCallBackRef;              /**< Rx Callback reference cookie         */
} HAL_Uart_t;

/************************* Function Prototypes ********************************/

/**
 * Initialize UART Driver
 * @param UartPtr  Pointer to user-allocated driver struct to initialize
 * @param UartID   ID of UART instance to initialize
 *                 0 = UART0
 *                 1 = UART1
 *
 * @return HAL_OK   on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Uart_Initialize(HAL_Uart_t * UartPtr, u8 UartID);

/**
 * Set Baudrate
 * @param UartPtr Pointer to UART driver struct
 * @param BaudDiv Baudrate divider
 *
 * @return HAL_OK on success, otherise HAL_ERROR
 */
extern HAL_Status_e HAL_Uart_SetBaudRate(HAL_Uart_t *UartPtr, u32 BaudDiv);

/**
 * Send data through UART
 * @param UartPtr Pointer to initialized HAL_Uart_t struct
 * @param BufPtr  Buffer containing data to send
 * @param Len   Length of data to send
 *
 * @return HAL_OK on success, otherwise HAL_ERROR or HAL_BUSY
 */
extern HAL_Status_e HAL_Uart_Send(HAL_Uart_t *UartPtr, u8 *BufPtr, u32 Len);

/**
 * Receive data through UART
 * @param UartPtr Pointer to initialized HAL_Uart_t struct
 * @param BufPtr  Buffer to contain data received
 * @param Len   Length of data to receive
 *
 * @return HAL_OK on success, otherwise HAL_ERROR or HAL_BUSY
 */
extern HAL_Status_e HAL_Uart_Recv(HAL_Uart_t *UartPtr, u8 *BufPtr, u32 Len);

/**
 * Enable UART Interrupts
 * @param UartPtr Pointer to initialized HAL_Uart_t struct
 *
 * @return HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Uart_EnableInterrupt(HAL_Uart_t *UartPtr);

/**
 * Disable UART Interrupts
 * @param UartPtr Pointer to initialized HAL_Uart_t struct
 *
 * @return HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Uart_DisableInterrupt(HAL_Uart_t * UartPtr);

/**
 * Set Receive Callback
 *
 * This is called when the driver has finished receiving the requested data
 *
 * @param UartPtr Pointer to initialized HAL_Uart_t struct
 * @param FuncPtr The callback function (called in interrupt context)
 *
 * @return HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Uart_SetRxCallback(HAL_Uart_t *UartPtr,
                                           HAL_Uart_CallBackFn FuncPtr);

/**
 * Set Transmit Callback
 *
 * This is called when the driver has finished sending the requested data
 *
 * @param UartPtr Pointer to initialized HAL_Uart_t struct
 * @param FuncPtr The callback function (called in interrupt context)
 *
 * @return HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Uart_SetTxCallback(HAL_Uart_t *UartPtr,
                                           HAL_Uart_CallBackFn FuncPtr);

/**
 * Clear UART Stats
 *
 * @param UartPtr Pointer to initialized HAL_Uart_t struct
 *
 * @return HAL_OK on success, otherwise HAL_ERROR
 */
extern HAL_Status_e HAL_Uart_ClearStats(HAL_Uart_t *UartPtr);

#ifdef __cplusplus
}
#endif

#endif /* AMBERM3VX_HAL_UART_H */
