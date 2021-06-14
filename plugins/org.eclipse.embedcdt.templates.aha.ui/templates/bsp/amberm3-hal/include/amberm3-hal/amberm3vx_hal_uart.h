#ifndef AMBERM3VX_HAL_UART_H
#define AMBERM3VX_HAL_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/************************* Includes *******************************************/
#include "amberm3vx.h"
#include "amberm3vx_hal_def.h"

/************************* Type Definitions ***********************************/

/**
 * Signature for UART callback function
 */
typedef void (*HAL_Uart_CallBack_Fn)(void *CallBackRef);

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
 * HAL UART Driver Instance Data
 */
typedef struct {
  Uart_RegDef_t *RegDefPtr;         /**< Pointer to register description      */
  HAL_Uart_Stats_t Stats;           /**< UART Statistics                      */
  u32 IsReady;                      /**< Device is ready                      */
  HAL_Uart_CallBack_Fn CallBack;    /**< Timer callback function              */
  void *CallBackRef;                /**< Callback reference cookie            */
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
 * Configure UART Device
 * @param UartPtr Pointer to UART driver struct
 * @param BaudDiv
 * @param TxEn
 * @param RxEn
 * @param TxIrqEn
 * @param RxIrqEn
 * @param TxOverIrqEn
 * @param RxOverIrqEn
 *
 * @return HAL_OK on success, otherise HAL_ERROR
 */
extern HAL_Status_e HAL_Uart_Configure(HAL_Uart_t *UartPtr, u32 BaudDiv, u32 TxEn,
                                    u32 RxEn,
                                    u32 TxIrqEn,
                                    u32 RxIrqEn,
                                    u32 TxOverIrqEn,
                                    u32 RxOverIrqEn);

/**
 * Returns whether UART RX Buffer is Full
 * @param UartPtr Pointer to UART driver struct
 *
 * @return 1 = FULL, 0 = NOT FULL
 */
extern u32 HAL_Uart_GetRxBufferFull(HAL_Uart_t *UartPtr);

/**
 * Returns whether UART TX Buffer is Full
 * @param UartPtr Pointer to UART driver struct
 *
 * @return 1 = FULL, 0 = NOT FULL
 */
extern u32 HAL_Uart_GetTxBufferFull(HAL_Uart_t *UartPtr);

/**
 * Sends a Character to UART TX Buffer
 * @param UartPtr Pointer to UART driver struct
 * @param Ch  Character to send
 *
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
extern HAL_Status_e HAL_Uart_SendChar(HAL_Uart_t *UartPtr, char Ch);

/**
 * Receives a Character to UART RX Buffer
 * @param UartPtr Pointer to UART driver struct
 *
 * @return Received character
 */
extern char HAL_Uart_ReceiveChar(HAL_Uart_t *UartPtr);

/**
 * Returns UART Overrun Status
 * @param UartPtr Pointer to UART driver struct
 *
 * @return Overrun status
 */
extern u32 HAL_Uart_GetOverrunStatus(HAL_Uart_t *UartPtr);

/**
 * Clears UART Overrun Status
 * @param UartPtr Pointer to UART driver struct
 *
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
extern HAL_Status_e HAL_Uart_ClearOverrunStatus(HAL_Uart_t *UartPtr);

/**
 * Returns UART Baud Rate Divider Value
 * @param UartPtr Pointer to UART driver struct
 *
 * @return Baud rate divider value
 */
extern u32 HAL_Uart_GetBaudDivider(HAL_Uart_t *UartPtr);

/**
 * Returns UART TX Interrupt Status
 * @param UartPtr Pointer to UART driver struct
 *
 * @return TX Interrupt Status
 */
extern u32 HAL_Uart_GetTxIRQStatus(HAL_Uart_t *UartPtr);

/**
 * Returns UART RX Interrupt Status
 * @param UartPtr Pointer to UART driver struct
 *
 * @return RX Interrupt Status
 */
extern u32 HAL_Uart_GetRxIRQStatus(HAL_Uart_t *UartPtr);

/**
 * Clears UART TX IRQ
 * @param UartPtr Pointer to UART driver struct
 *
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
extern HAL_Status_e HAL_Uart_ClearTxIRQ(HAL_Uart_t *UartPtr);

/**
 * Clears UART RX IRQ
 * @param UartPtr Pointer to UART driver struct
 *
 * @return HAL_OK on success, HAL_ERROR otherwise
 */
extern HAL_Status_e HAL_Uart_ClearRxIRQ(HAL_Uart_t *UartPtr);

#ifdef __cplusplus
}
#endif

#endif /* AMBERM3VX_HAL_UART_H */
