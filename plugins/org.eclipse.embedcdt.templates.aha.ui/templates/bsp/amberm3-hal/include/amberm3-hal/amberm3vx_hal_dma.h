#ifndef AMBERM3VX_HAL_DMA_H
#define AMBERM3VX_HAL_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/************************* Includes *******************************************/
#include "amberm3vx.h"
#include "amberm3vx_hal_def.h"

/************************* Constant Definitions *******************************/
#define HAL_DMA_0                   0
#define HAL_DMA_1                   1

#define HAL_DMA_CHAN_0              0
#define HAL_DMA_CHAN_1              1

#define HAL_DMA_CHAN_FREE           0
#define HAL_DMA_CHAN_BUSY           1

/************************* Type Definitions ***********************************/
typedef struct {
  u32 DmaID;
  u32 IsReady;
  volatile u32 ChanStatus[2];
} HAL_Dma_t;

typedef struct {
  u32 DmaChannel;
  u32 BurstLength;      /* Number of 64-bit beats per burst (1-16) */
  u32 NumBursts;        /* Number of bursts to perform (1-256) */
  void *DestAddr;
  void *SrcAddr;
} HAL_Dma_XferConfig;

/************************* Function Prototypes ********************************/

/**
 * Initializes DMA Driver for the DMA with given ID
 * @param DmaPtr  User-allocated HAL_Dma_t struct to initialize
 * @param DmaID   The ID of the DMA to initialize
 *
 * @return HAL_OK on success, otherwise HAL_ERROR
 */
HAL_Status_e HAL_Dma_Initialize(HAL_Dma_t *DmaPtr, u32 DmaID);

/**
 * Transfer a block of data from a source to a destination
 * @param DmaPtr  Pointer to an initialized HAL_Dma_t struct
 * @param XferConfig  Transfer configuration
 *
 * @note:
 * Maximum transferrable buffer size is 8 Bytes * 16 * 256 = 32768 Bytes (32KB)
 *
 * @return HAL_OK on success, otherwise HAL_ERROR
 */
HAL_Status_e HAL_Dma_StartXfer(HAL_Dma_t *DmaPtr, HAL_Dma_XferConfig XferConfig);

/**
 * Wait on transfer completion from specified DMA channel
 * @param DmaPtr  Pointer to an initialized HAL_Dma_t struct
 * @param DmaChannel DMA channel to wait on
 *
 * @note:
 * This performs a blocking wait
 *
 * @return HAL_OK on success, otherwise HAL_ERROR
 */
HAL_Status_e HAL_Dma_Wait(HAL_Dma_t *DmaPtr, u32 DmaChannel);

/**
 * DMA Transfer call (blocking)
 * @param DmaPtr Pointer to an initialized HAL_Dma_t struct
 * @param DestAddr  The destination address for the transfer (64-bit aligned)
 * @param SrcAddr   The Source addres for the transfer (64-bit aligned)
 * @param Length    The length of the transfer (can be greater than 32KB)
 *
 * @return HAL_OK on success, otherwise HAL_ERROR
 */
HAL_Status_e HAL_Dma_Xfer(HAL_Dma_t *DmaPtr, void *DestAddr, void *SrcAddr,
                          u32 Length);

#ifdef __cplusplus
}
#endif

#endif /* AMBERM3VX_HAL_DMA_H */
