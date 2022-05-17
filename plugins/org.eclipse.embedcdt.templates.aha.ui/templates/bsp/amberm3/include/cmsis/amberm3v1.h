/*******************************************************************************
 * @file    amberm3v1.h
 * @brief   CMSIS Core Peripheral Access Layer File for AMBERM3V1 Device
 * @version V5.3.1
 *
 ******************************************************************************/

#ifndef AMBERM3V1_H
#define AMBERM3V1_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/**************************** Configuration of Core Peripherals ***************/
#define __CM3_REV                 0x0200U   /* Core revision r2p0             */
#define __MPU_PRESENT             1U        /* AMBERM3V1 provides an MPU      */
#define __VTOR_PRESENT            1U        /* Cortex-M3 has support for VTOR */
#define __NVIC_PRIO_BITS          3U        /* AMBERM3V1 uses 3 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used  */

/**************************** Interrupt Number Definition *********************/
typedef enum
{
/**************************** Processor Exceptions Numbers ********************/
  NonMaskableInt_IRQn         = -14,    /* 2 Non Maskable Interrupt (Watchdog Irq)  */
  HardFault_IRQn              = -13,    /* 3 Hard Fault Interrupt                   */
  MemoryManagement_IRQn       = -12,    /* 4 Cortex-M3 Memory Management Interrupt  */
  BusFault_IRQn               = -11,    /* 5 Cortex-M3 Bus Fault Interrupt          */
  UsageFault_IRQn             = -10,    /* 6 Cortex-M3 Usage Fault Interrupt        */
  SVCall_IRQn                 = -5,     /* 11 Cortex-M3 SV Call Interrupt           */
  DebugMonitor_IRQn           = -4,     /* 12 Cortex-M3 Debug Monitor Interrupt     */
  PendSV_IRQn                 = -2,     /* 14 Cortex-M3 Pend SV Interrupt           */
  SysTick_IRQn                = -1,     /* 15 Cortex-M3 System Tick Interrupt       */

/**************************** Processor Interrupt Numbers *********************/

  TIMER0_IRQn                 = 0,      /* TIMER0 Interrupt                   */
  TIMER1_IRQn                 = 1,      /* TIMER1 Interrupt                   */
  UART0_IRQn                  = 2,      /* UART0 Interrupt                    */
  UART1_IRQn                  = 3,      /* UART1 Interrupt                    */
  UARTOVF_IRQn                = 4,      /* UART0/1 Overflow                   */
  DMA0_0_IRQn                 = 5,      /* DMA0 Interrupt 0                   */
  DMA0_1_IRQn                 = 6,      /* DMA0 Interrupt 1                   */
  DMA1_0_IRQn                 = 7,      /* DMA1 Interrupt 0                   */
  DMA1_1_IRQn                 = 8,      /* DMA1 Interrupt 1                   */
  CGRA_IRQn                   = 9,      /* CGRA Interrupt                     */
  TLX_IRQn                    = 10     /* TLX Interrupt                       */
  /* Interrupts 11 .. 224 are left out */
} IRQn_Type;

#include "core_cm3.h"
#include "system_amberm3vx.h"

/**************************** Peripheral Register Definitions   ***************/

/****************************** Timer (TIMER) *********************************/
typedef struct {
  __IO uint32_t CTRL;               /* Offset: 0x000 Control Register (R/W) */
  __IO uint32_t VALUE;              /* Offset: 0x004 Current Value Register (R/W) */
  __IO uint32_t RELOAD;             /* Offset: 0x008 Reload Value Register  (R/W) */
  union {
         __I uint32_t INTSTATUS;    /* Offset: 0x00C Interrupt Status Register (R/ ) */
         __O uint32_t INTCLEAR;     /* Offset: 0x00C Interrupt Clear Register ( /W) */
  };
} Timer_RegDef_t;

#define TIMER_CTRL_IRQEN_Pos        3
#define TIMER_CTRL_IRQEN_Msk        (0x01ul << TIMER_CTRL_IRQEN_Pos)

#define TIMER_CTRL_SELEXTCLK_Pos    2
#define TIMER_CTRL_SELEXTCLK_Msk    (0x01ul << TIMER_CTRL_SELEXTCLK_Pos)

#define TIMER_CTRL_SELEXTEN_Pos     1
#define TIMER_CTRL_SELEXTEN_Msk     (0x01ul << TIMER_CTRL_SELEXTEN_Pos)

#define TIMER_CTRL_EN_Pos           0
#define TIMER_CTRL_EN_Msk           (0x01ul << TIMER_CTRL_EN_Pos)

#define TIMER_VAL_CURRENT_Pos       0
#define TIMER_VAL_CURRENT_Msk       (0xFFFFFFFFul << TIMER_VAL_CURRENT_Pos)

#define TIMER_RELOAD_VAL_Pos        0
#define TIMER_RELOAD_VAL_Msk        (0xFFFFFFFFul << TIMER_RELOAD_VAL_Pos)

#define TIMER_INTSTATUS_Pos         0
#define TIMER_INTSTATUS_Msk         (0x01ul << TIMER_INTSTATUS_Pos)

#define TIMER_INTCLEAR_Pos          0
#define TIMER_INTCLEAR_Msk          (0x01ul << TIMER_INTCLEAR_Pos)

/****************************** UART ******************************************/
typedef struct {
  __IO uint32_t DATA;               /*!< Offset: 0x000 Data Register    (R/W) */
  __IO uint32_t STATE;              /*!< Offset: 0x004 Status Register  (R/W) */
  __IO uint32_t CTRL;               /*!< Offset: 0x008 Control Register (R/W) */
  union {
          __I uint32_t INTSTATUS;   /*!< Offset: 0x00C Interrupt Status Register (R/ ) */
          __O uint32_t INTCLEAR;    /*!< Offset: 0x00C Interrupt Clear Register ( /W) */
  };
  __IO uint32_t BAUDDIV;            /*!< Offset: 0x010 Baudrate Divider Register (R/W) */
} Uart_RegDef_t;

#define UART_DATA_Pos               0
#define UART_DATA_Msk               (0xFFul << UART_DATA_Pos)

#define UART_STATE_RXOR_Pos         3
#define UART_STATE_RXOR_Msk         (0x1ul << UART_STATE_RXOR_Pos)

#define UART_STATE_TXOR_Pos         2
#define UART_STATE_TXOR_Msk         (0x1ul << UART_STATE_TXOR_Pos)

#define UART_STATE_RXBF_Pos         1
#define UART_STATE_RXBF_Msk         (0x1ul << UART_STATE_RXBF_Pos)

#define UART_STATE_TXBF_Pos         0
#define UART_STATE_TXBF_Msk         (0x1ul << UART_STATE_TXBF_Pos )

#define UART_CTRL_HSTM_Pos          6
#define UART_CTRL_HSTM_Msk          (0x01ul << UART_CTRL_HSTM_Pos)

#define UART_CTRL_RXORIRQEN_Pos     5
#define UART_CTRL_RXORIRQEN_Msk     (0x01ul << UART_CTRL_RXORIRQEN_Pos)

#define UART_CTRL_TXORIRQEN_Pos     4
#define UART_CTRL_TXORIRQEN_Msk     (0x01ul << UART_CTRL_TXORIRQEN_Pos)

#define UART_CTRL_RXIRQEN_Pos       3
#define UART_CTRL_RXIRQEN_Msk       (0x01ul << UART_CTRL_RXIRQEN_Pos)

#define UART_CTRL_TXIRQEN_Pos       2
#define UART_CTRL_TXIRQEN_Msk       (0x01ul << UART_CTRL_TXIRQEN_Pos)

#define UART_CTRL_RXEN_Pos          1
#define UART_CTRL_RXEN_Msk          (0x01ul << UART_CTRL_RXEN_Pos)

#define UART_CTRL_TXEN_Pos          0
#define UART_CTRL_TXEN_Msk          (0x01ul << UART_CTRL_TXEN_Pos)

#define UART_INTSTATUS_RXORIRQ_Pos  3
#define UART_CTRL_RXORIRQ_Msk       (0x01ul << UART_INTSTATUS_RXORIRQ_Pos)

#define UART_CTRL_TXORIRQ_Pos       2
#define UART_CTRL_TXORIRQ_Msk       (0x01ul << UART_CTRL_TXORIRQ_Pos)

#define UART_CTRL_RXIRQ_Pos         1
#define UART_CTRL_RXIRQ_Msk         (0x01ul << UART_CTRL_RXIRQ_Pos)

#define UART_CTRL_TXIRQ_Pos         0
#define UART_CTRL_TXIRQ_Msk         (0x01ul << UART_CTRL_TXIRQ_Pos)

#define UART_BAUDDIV_Pos            0
#define UART_BAUDDIV_Msk            (0xFFFFFul << UART_BAUDDIV_Pos)

/****************************** Watchdog Timer (WDOG) *************************/
typedef struct {
  __IO uint32_t LOAD;               /* Offset: 0x000 (R/W) Watchdog Load Register */
  __I uint32_t VALUE;               /* Offset: 0x004 (R/ ) Watchdog Value Register */
  __IO uint32_t CTRL;               /* Offset: 0x008 (R/W) Watchdog Control Register */
  __O uint32_t INTCLR;              /* Offset: 0x00C ( /W) Watchdog Clear Interrupt Register */
  __I uint32_t RAWINTSTAT;          /* Offset: 0x010 (R/ ) Watchdog Raw Interrupt Status Register */
  __I uint32_t MASKINTSTAT;         /* Offset: 0x014 (R/ ) Watchdog Interrupt Status Register */
  uint32_t RESERVED0[762];
  __IO uint32_t LOCK;               /* Offset: 0xC00 (R/W) Watchdog Lock Register */
  uint32_t RESERVED1[191];
  __IO uint32_t ITCR;               /* Offset: 0xF00 (R/W) Watchdog Integration Test Control Register */
  __O uint32_t ITOP;                /* Offset: 0xF04 ( /W) Watchdog Integration Test Output Set Register */

} Wdog_RegDef_t;

#define WDOG_LOAD_Pos               0
#define WDOG_LOAD_Msk               (0xFFFFFFFFul << WDOG_LOAD_Pos)

#define WDOG_VALUE_Pos              0
#define WDOG_VALUE_Msk              (0xFFFFFFFFul << WDOG_VALUE_Pos)

#define WDOG_CTRL_RESEN_Pos         1
#define WDOG_CTRL_RESEN_Msk         (0x1ul << WDOG_CTRL_RESEN_Pos)

#define WDOG_CTRL_INTEN_Pos         0
#define WDOG_CTRL_INTEN_Msk         (0x1ul << WDOG_CTRL_INTEN_Pos)

#define WDOG_INTCLR_Pos             0
#define WDOG_INTCLR_Msk             (0x1ul << WDOG_INTCLR_Pos)

#define WDOG_RAWINTSTAT_Pos         0
#define WDOG_RAWINTSTAT_Msk         (0x1ul << WDOG_RAWINTSTAT_Pos)

#define WDOG_MASKINTSTAT_Pos        0
#define WDOG_MASKINTSTAT_Msk        (0x1ul << WDOG_MASKINTSTAT_Pos)

#define WDOG_LOCK_Pos               0
#define WDOG_LOCK_Msk               (0x1ul << WDOG_LOCK_Pos)

#define WDOG_INTEGTESTEN_Pos        0
#define WDOG_INTEGTESTEN_Msk        (0x1ul << WDOG_INTEGTESTEN_Pos)

#define WDOG_INTEGTESTOUTSET_Pos    1
#define WDOG_INTEGTESTOUTSET_Msk    (0x1ul << WDOG_INTEGTESTOUTSET_Pos)

/****************************** Platform Controller (PtfmCtrl) *****************/
typedef struct {
  __IO  uint32_t  ID;                   /* Offset: 0x000 (R/W)  ID Register */
  __IO  uint32_t  PAD_STRENGTH_CTRL;    /* Offset: 0x004 (R/W ) Pad Strength Control Register */
  __IO  uint32_t  SYS_CLK_SELECT;       /* Offset: 0x008 (R/W)  System Clock Selection Register */
       uint32_t  RESERVED0[2];
  __IO  uint32_t  DMA0_PCLK_SELECT;     /* Offset: 0x014 (R/W)  DMA0 Peripheral Clock Selection Register */
  __IO  uint32_t  DMA1_PCLK_SELECT;     /* Offset: 0x018 (R/W)  DMA0 Peripheral Clock Selection Register */
       uint32_t  RESERVED1;
  __IO  uint32_t  TLX_FWD_CLK_SELECT;   /* Offset: 0x020 (R/W)  TLX Fwd Clock Selection Register */
       uint32_t  RESERVED2;
  __IO  uint32_t  CGRA_CLK_SELECT;      /* Offset: 0x028 (R/W)  CGRA Clock Selection Register */
       uint32_t  RESERVED3;
  __IO  uint32_t  TIMER0_CLK_SELECT;    /* Offset: 0x030 (R/W)  Timer0 Clock Selection Register */
  __IO  uint32_t  TIMER1_CLK_SELECT;    /* Offset: 0x034 (R/W)  Timer1 Clock Selection Register */
  __IO  uint32_t  UART0_CLK_SELECT;     /* Offset: 0x038 (R/W)  UART0 Clock Selection Register */
  __IO  uint32_t  UART1_CLK_SELECT;     /* Offset: 0x03C (R/W)  UART1 Clock Selection Register */
  __IO  uint32_t  WDOG_CLK_SELECT;      /* Offset: 0x040 (R/W)  Watchdog Clock Selection Register */
  __IO  uint32_t  CLK_GATE_EN;          /* Offset: 0x044 (R/W)  Clock Gate Enable Register */
  __IO  uint32_t  SYS_RESET_PROPAGATE;  /* Offset: 0x048 (R/W)  System Reset Propagation Register */
  __IO  uint32_t  RESET_REQ;            /* Offset: 0x04C (R/W)  Peripheral Reset Request Register */
  __I   uint32_t  RESET_ACK;            /* Offset: 0x050 (R/ )  Peripheral Reset Request Register */
  __IO  uint32_t  SYS_TICK_CONFIG;      /* Offset: 0x054 (R/W)  Systick Configuration Register */
  __IO  uint32_t  SYS_RESET_AGGREGATE;  /* Offset: 0x058 (R/W)  System Reset Source Aggregation Register */
  __IO  uint32_t  MASTER_CLK_SELECT;    /* Offset: 0x05C (R/W)  Master Clock Source Select */

} PtfmCtrl_RegDef_t;

#define PTFMCTRL_SYS_Pos            0
#define PTFMCTRL_CPU_Pos            1
#define PTFMCTRL_DAP_Pos            2
#define PTFMCTRL_DMA0_Pos           3
#define PTFMCTRL_DMA1_Pos           4
#define PTFMCTRL_SRAM_Pos           5
#define PTFMCTRL_TLX_FWD_Pos        6
#define PTFMCTRL_TLX_REV_Pos        7
#define PTFMCTRL_CGRA_Pos           8
#define PTFMCTRL_NIC_Pos            9
#define PTFMCTRL_TIMER0_Pos         10
#define PTFMCTRL_TIMER1_Pos         11
#define PTFMCTRL_UART0_Pos          12
#define PTFMCTRL_UART1_Pos          13
#define PTFMCTRL_WDOG_Pos           14

/****************************** TLX Controller ********************************/
typedef struct {
  __IO  uint32_t  ID;                   /* Offset: 0x000 (R/W)  ID Register */
  __IO  uint32_t  LANE_EN;              /* Offset: 0x004 (R/W ) Lane Enable Register */
  __IO  uint32_t  LANE_IE;              /* Offset: 0x008 (R/W ) Lane Interrupt Enable Register */
  __IO  uint32_t  LANE_START;           /* Offset: 0x00C (R/W ) Lane START Register */
  __IO  uint32_t  LANE_CLEAR;           /* Offset: 0x010 (R/W ) Lane CLEAR Register */
  __IO  uint32_t  LANE_INT_STATUS;      /* Offset: 0x014 (R/W ) Lane Interrupt Status Register */
  __IO  uint32_t  LANE_STATUS;          /* Offset: 0x018 (R/W ) Lane Status Register */
  __IO  uint32_t  LANE0_SEQUENCE;       /* Offset: 0x01C (R/W ) Lane0 Sequence Register */
  __IO  uint32_t  LANE1_SEQUENCE;       /* Offset: 0x020 (R/W ) Lane1 Sequence Register */
  __IO  uint32_t  LANE2_SEQUENCE;       /* Offset: 0x024 (R/W ) Lane2 Sequence Register */
  __IO  uint32_t  LANE3_SEQUENCE;       /* Offset: 0x028 (R/W ) Lane3 Sequence Register */
  __IO  uint32_t  LANE4_SEQUENCE;       /* Offset: 0x02C (R/W ) Lane4 Sequence Register */
  __IO  uint32_t  LANE5_SEQUENCE;       /* Offset: 0x030 (R/W ) Lane5 Sequence Register */
  __IO  uint32_t  LANE6_SEQUENCE;       /* Offset: 0x034 (R/W ) Lane6 Sequence Register */
  __IO  uint32_t  LANE7_SEQUENCE;       /* Offset: 0x038 (R/W ) Lane7 Sequence Register */
  __IO  uint32_t  LANE8_SEQUENCE;       /* Offset: 0x03C (R/W ) Lane8 Sequence Register */
  __IO  uint32_t  LANE9_SEQUENCE;       /* Offset: 0x040 (R/W ) Lane9 Sequence Register */
  __IO  uint32_t  LANE0_LENGTH;         /* Offset: 0x044 (R/W ) Lane0 Length Register */
  __IO  uint32_t  LANE1_LENGTH;         /* Offset: 0x048 (R/W ) Lane1 Length Register */
  __IO  uint32_t  LANE2_LENGTH;         /* Offset: 0x04C (R/W ) Lane2 Length Register */
  __IO  uint32_t  LANE3_LENGTH;         /* Offset: 0x050 (R/W ) Lane3 Length Register */
  __IO  uint32_t  LANE4_LENGTH;         /* Offset: 0x054 (R/W ) Lane4 Length Register */
  __IO  uint32_t  LANE5_LENGTH;         /* Offset: 0x058 (R/W ) Lane5 Length Register */
  __IO  uint32_t  LANE6_LENGTH;         /* Offset: 0x05C (R/W ) Lane6 Length Register */
  __IO  uint32_t  LANE7_LENGTH;         /* Offset: 0x060 (R/W ) Lane7 Length Register */
  __IO  uint32_t  LANE8_LENGTH;         /* Offset: 0x064 (R/W ) Lane8 Length Register */
  __IO  uint32_t  LANE9_LENGTH;         /* Offset: 0x068 (R/W ) Lane9 Length Register */
  __I   uint32_t  LANE0_MATCH;          /* Offset: 0x06C (R/W ) Lane0 Match Count Register */
  __I   uint32_t  LANE1_MATCH;          /* Offset: 0x070 (R/W ) Lane1 Match Count Register */
  __I   uint32_t  LANE2_MATCH;          /* Offset: 0x074 (R/W ) Lane2 Match Count Register */
  __I   uint32_t  LANE3_MATCH;          /* Offset: 0x078 (R/W ) Lane3 Match Count Register */
  __I   uint32_t  LANE4_MATCH;          /* Offset: 0x07C (R/W ) Lane4 Match Count Register */
  __I   uint32_t  LANE5_MATCH;          /* Offset: 0x080 (R/W ) Lane5 Match Count Register */
  __I   uint32_t  LANE6_MATCH;          /* Offset: 0x084 (R/W ) Lane6 Match Count Register */
  __I   uint32_t  LANE7_MATCH;          /* Offset: 0x088 (R/W ) Lane7 Match Count Register */
  __I   uint32_t  LANE8_MATCH;          /* Offset: 0x08C (R/W ) Lane8 Match Count Register */
  __I   uint32_t  LANE9_MATCH;          /* Offset: 0x090 (R/W ) Lane9 Match Count Register */
} TlxCtrl_RegDef_t;

/****************************** CGRA ******************************************/

/****************************** Peripheral Memory Map *************************/

/* Base Addresses */
#define AMBERM3V1_ROM_BASE          (0x00000000UL)
#define AMBERM3V1_SRAM_BASE         (0x20000000UL)
#define AMBERM3V1_PERIPH_BASE       (0x40000000UL)
#define AMBERM3V1_RAM_BASE          (0x60000000UL)
#define AMBERM3V1_TLXCTRL_BASE      (0x40014000UL)
#define AMBERM3V1_CGRA_GLB_BASE     (0x20400000UL)
#define AMBERM3V1_CGRA_GLC_BASE     (0x40010000UL)

/* Aliases */
#define AMBERM3V1_TLX_BASE          AMBERM3V1_RAM_BASE
#define AMBERM3V1_APB_BASE          AMBERM3V1_PERIPH_BASE

/* Peripheral Memory Sizes */
#define AMBERM3V1_ROM_SIZE          (0x10000UL)
#define AMBERM3V1_SRAM_SIZE         (0x20000UL)
#define AMBERM3V1_PERIPH_SIZE       (0x10000UL)
#define AMBERM3V1_RAM_SIZE          (0x40000000UL)
#define AMBERM3V1_CGRA_GLB_SIZE     (0x0x400000UL)
#define AMBERM3V1_CGRA_GLC_SIZE     (0x2000UL)

/* Aliases */
#define AMBERM3V1_TLX_SIZE          AMBERM3V1_RAM_SIZE
#define AMBERM3V1_APB_SIZE          AMBERM3V1_PERIPH_SIZE

/* Peripheral Addresses */
#define AMBERM3V1_TIMER0_BASE       (AMBERM3V1_APB_BASE + 0x0000UL)
#define AMBERM3V1_TIMER1_BASE       (AMBERM3V1_APB_BASE + 0x1000UL)
#define AMBERM3V1_UART0_BASE        (AMBERM3V1_APB_BASE + 0x2000UL)
#define AMBERM3V1_UART1_BASE        (AMBERM3V1_APB_BASE + 0x3000UL)
#define AMBERM3V1_WDOG_BASE         (AMBERM3V1_APB_BASE + 0x4000UL)
#define AMBERM3V1_DMA0_BASE         (AMBERM3V1_APB_BASE + 0x5000UL)
#define AMBERM3V1_DMA1_BASE         (AMBERM3V1_APB_BASE + 0x6000UL)
#define AMBERM3V1_PTFMCTRL_BASE     (AMBERM3V1_APB_BASE + 0x7000UL)

/****************************** Peripheral Declarations ************************/
#define Device_TIMER0               ((Timer_RegDef_t    *) AMBERM3V1_TIMER0_BASE)
#define Device_TIMER1               ((Timer_RegDef_t    *) AMBERM3V1_TIMER1_BASE)
#define Device_UART0                ((Uart_RegDef_t     *) AMBERM3V1_UART0_BASE)
#define Device_UART1                ((Uart_RegDef_t     *) AMBERM3V1_UART1_BASE)
#define Device_WDOG                 ((Wdog_RegDef_t     *) AMBERM3V1_WDOG_BASE)
#define Device_PTFMCTRL             ((PtfmCtrl_RegDef_t *) AMBERM3V1_PTFMCTRL_BASE)
#define Device_TLXCTRL              ((TlxCtrl_RegDef_t  *) AMBERM3V1_TLXCTRL_BASE)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AMBERM3V1_H */
