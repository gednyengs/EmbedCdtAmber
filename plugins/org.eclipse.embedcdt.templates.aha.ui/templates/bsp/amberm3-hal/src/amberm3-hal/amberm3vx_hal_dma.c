#include "amberm3vx_hal_dma.h"

/************************* Constant Definitions *******************************/

#define DMA0_BASE                   AMBERM3V1_DMA0_BASE
#define DMA0_DBGCMD                 ((volatile u32 *)(DMA0_BASE + 0xD04))
#define DMA0_DBGINST0               ((volatile u32 *)(DMA0_BASE + 0xD08))
#define DMA0_DBGINST1               ((volatile u32 *)(DMA0_BASE + 0xD0C))
#define DMA0_INTEN                  ((volatile u32 *)(DMA0_BASE + 0x020))
#define DMA0_INTCLR                 ((volatile u32 *)(DMA0_BASE + 0x02C))

#define DMA1_BASE                   AMBERM3V1_DMA1_BASE
#define DMA1_DBGCMD                 ((volatile u32 *)(DMA1_BASE + 0xD04))
#define DMA1_DBGINST0               ((volatile u32 *)(DMA1_BASE + 0xD08))
#define DMA1_DBGINST1               ((volatile u32 *)(DMA1_BASE + 0xD0C))
#define DMA1_INTEN                  ((volatile u32 *)(DMA1_BASE + 0x020))
#define DMA1_INTCLR                 ((volatile u32 *)(DMA1_BASE + 0x02C))

/************************* Variable Definitions *******************************/

static u32 DmaCode0[] = {
  0xC00701BC,
  0x00BC0001,
  0x200000C0,
  0x10C002BC,
  0x0F202000,
  0x02380804,
  0xFF000034
};

static u32 DmaCode1[] = {
  0xC00701BC,
  0x00BC0001,
  0x200000C0,
  0x10C002BC,
  0x0F202000,
  0x02380804,
  0xFF000034
};

static volatile u32 Dma0IRQCounter;
static volatile u32 Dma1IRQCounter;

/************************* Helper Functions ***********************************/

static void HAL_Dma_SetCode(void *DestAddr, void *SrcAddr, u32 BurstLength,
                            u32 NumBursts, u32 *DmaCode)
{
  u32 ccr0 = 0xC0070000;
  u32 ccr1 = 0x0001;
  ccr0 |= (BurstLength - 1) << 20;
  ccr1 |= (BurstLength - 1) << 2;
  DmaCode[0] = ccr0 | 0x01BC;
  DmaCode[1] = 0x00BC0000 | ccr1;
  DmaCode[2] = (u32) SrcAddr;
  DmaCode[3] = ((u32) DestAddr << 16) | 0x02BC;
  DmaCode[4] = ((NumBursts - 1) << 24) | 0x00200000 | ((u32) DestAddr >> 16);
}

/************************* Function Definitions *******************************/

HAL_Status_e HAL_Dma_Initialize(HAL_Dma_t *DmaPtr, u32 DmaID)
{
  assert_param(DmaPtr != NULL);

  if (DmaID == HAL_DMA_0 || DmaID == HAL_DMA_1) {
    DmaPtr->DmaID = DmaID;
    DmaPtr->IsReady = 1;
    DmaPtr->ChanStatus[0] = HAL_DMA_CHAN_FREE;
    DmaPtr->ChanStatus[1] = HAL_DMA_CHAN_FREE;
    return HAL_OK;
  }

  DmaPtr->IsReady = 0;

  return HAL_ERROR;
}

HAL_Status_e HAL_Dma_StartXfer(HAL_Dma_t *DmaPtr, HAL_Dma_XferConfig XferConfig)
{
  assert_param(DmaPtr != NULL);
  assert_param(DmaPtr->IsReady == 1);
  assert_param(XferConfig.DmaChannel == 0);

  if (DmaPtr->ChanStatus[0] != HAL_DMA_CHAN_FREE)
    return HAL_ERROR;

  if (DmaPtr->DmaID == HAL_DMA_0) {
    HAL_Dma_SetCode(XferConfig.DestAddr, XferConfig.SrcAddr,
                    XferConfig.BurstLength,
                    XferConfig.NumBursts,
                    DmaCode0);
    // DMAGO instruction on channel 0
    *DMA0_DBGINST0 = 0x00A00000;
    // Set Address of first instruction
    *DMA0_DBGINST1 = (u32) DmaCode0;
    // Enable DMA0 Interrupt
    *DMA0_INTEN = 0x01;
    NVIC_ClearPendingIRQ(DMA0_0_IRQn);
    NVIC_EnableIRQ(DMA0_0_IRQn);
    // Instruct DMA to execute instructions
    DmaPtr->ChanStatus[0] = HAL_DMA_CHAN_BUSY;
    Dma0IRQCounter = 0;
    *DMA0_DBGCMD = 0x0;

    return HAL_OK;
  } else if(DmaPtr->DmaID == HAL_DMA_1) {
    HAL_Dma_SetCode(XferConfig.DestAddr, XferConfig.SrcAddr,
                    XferConfig.BurstLength,
                    XferConfig.NumBursts,
                    DmaCode1);
    // DMAGO instruction on channel 0
    *DMA1_DBGINST0 = 0x00A00000;
    // Set Address of first instruction
    *DMA1_DBGINST1 = (u32) DmaCode1;
    // Enable DMA0 Interrupt
    *DMA1_INTEN = 0x01;
    NVIC_ClearPendingIRQ(DMA1_0_IRQn);
    NVIC_EnableIRQ(DMA1_0_IRQn);
    // Instruct DMA to execute instructions
    DmaPtr->ChanStatus[0] = HAL_DMA_CHAN_BUSY;
    Dma1IRQCounter = 0;
    *DMA1_DBGCMD = 0x0;

    return HAL_OK;
  }

  return HAL_ERROR;
}

HAL_Status_e HAL_Dma_Wait(HAL_Dma_t *DmaPtr, u32 DmaChannel)
{
  assert_param(DmaPtr != NULL);
  assert_param(DmaPtr->IsReady == 1);
  assert_param(DmaChannel == 0);

  if (DmaPtr->DmaID == HAL_DMA_0) {
    while (Dma0IRQCounter == 0);
    Dma0IRQCounter = 0;
    NVIC_ClearPendingIRQ(DMA0_0_IRQn);

  } else if (DmaPtr->DmaID == HAL_DMA_1) {
    while (Dma1IRQCounter == 0);
    Dma1IRQCounter = 0;
    NVIC_ClearPendingIRQ(DMA1_0_IRQn);
  }

  DmaPtr->ChanStatus[0] = HAL_DMA_CHAN_FREE;

  return HAL_OK;
}

HAL_Status_e HAL_Dma_Xfer(HAL_Dma_t *DmaPtr, void *DestAddr, void *SrcAddr,
                          u32 Length)
{
  HAL_Status_e Status;
  HAL_Dma_XferConfig XferConfig;

  assert_param(DmaPtr != NULL);
  assert_param(DmaPtr->IsReady == 1);
  assert_param(DestAddr != NULL);
  assert_param(SrcAddr != NULL);

  if (DmaPtr->ChanStatus[0] != HAL_DMA_CHAN_FREE)
    return HAL_ERROR;

  if (((((u32) DestAddr) & 0x7) != 0) || ((((u32) SrcAddr) & 0x7) != 0))
    return HAL_ERROR;

  u64 *DAddr = (u64 *) DestAddr;
  u64 *SAddr = (u64 *) SrcAddr;

  u32 log_burst_length = 4;
  while (Length > 0) {
    u32 burst_length = 1 << log_burst_length;
    while (Length >= burst_length) {
      u32 bursts_left = Length >> log_burst_length;
      u32 bursts_to_do = bursts_left > 256 ? 256 : bursts_left;
      XferConfig.DmaChannel = HAL_DMA_CHAN_0;
      XferConfig.BurstLength = burst_length;
      XferConfig.NumBursts = bursts_to_do;
      XferConfig.DestAddr = DAddr;
      XferConfig.SrcAddr = SAddr;
      Status = HAL_Dma_StartXfer(DmaPtr, XferConfig);
      if (Status != HAL_OK) {
        return Status;
      }
      Status = HAL_Dma_Wait(DmaPtr, HAL_DMA_CHAN_0);
      if (Status != HAL_OK) {
        return Status;
      }
      u32 beats_done = bursts_to_do << log_burst_length;
      DAddr += beats_done;
      SAddr += beats_done;
      if (Length > beats_done)
        Length -= beats_done;
      else
        Length = 0;
    }
    log_burst_length -= 1;
  }

  return HAL_OK;
}


/************************* Interrupt Handlers  ********************************/

void DMA0_0_IRQHandler(void)
{
  Dma0IRQCounter = 1;
  *DMA0_INTCLR = 0x01;
}

void DMA1_0_IRQHandler(void)
{
  Dma1IRQCounter = 1;
  *DMA1_INTCLR = 0x01;
}
