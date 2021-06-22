/**
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// The list of external handlers is from the Arm assembly startup files.

// ----------------------------------------------------------------------------

#include <cortexm/exception-handlers.h>

// ----------------------------------------------------------------------------

void __attribute__((weak))
Default_Handler(void);

// Forward declaration of the specific IRQ handlers. These are aliased
// to the Default_Handler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions

void __attribute__ ((weak, alias ("Default_Handler")))
TIMER0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TIMER1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
UART_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA0_0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA0_1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_0_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
DMA1_1_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
CGRA_IRQHandler(void);
void __attribute__ ((weak, alias ("Default_Handler")))
TLX_IRQHandler(void);

// ----------------------------------------------------------------------------

/* Defined in linker script */
extern unsigned int __stack;

typedef void(* const IRQHandler)(void);

// ----------------------------------------------------------------------------

// The table of interrupt handlers. It has an explicit section name
// and relies on the linker script to place it at the correct location
// in memory.

__attribute__ ((section(".isr_vectors"),used))
IRQHandler __isr_vectors[] =
  {
    // Cortex-M Core Handlers
    (IRQHandler) &__stack,             // The initial stack pointer
    Reset_Handler,                     // The reset handler

    NMI_Handler,                       // The NMI handler
    HardFault_Handler,                 // The hard fault handler

#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    MemManage_Handler,                  // The MPU fault handler
    BusFault_Handler,                   // The bus fault handler
    UsageFault_Handler,                 // The usage fault handler
#else
    0,                                  // Reserved
    0,                                  // Reserved
    0,                                  // Reserved
#endif
    0,                                  // Reserved
    0,                                  // Reserved
    0,                                  // Reserved
    0,                                  // Reserved
    SVC_Handler,                        // SVCall handler
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    DebugMon_Handler,                   // Debug monitor handler
#else
    0,                                  // Reserved
#endif
    0,                                  // Reserved
    PendSV_Handler,                     // The PendSV handler
    SysTick_Handler,                    // The SysTick handler

    // ----------------------------------------------------------------------
    // External Interrupts
    TIMER0_IRQHandler,                  // TIMER0 Interrupt Handler
    TIMER1_IRQHandler,                  // TIMER1 Interrupt Handler
    UART_IRQHandler,                    // UART0 Interrupt Handler
    UART_IRQHandler,                    // UART1 Interrupt Handler
    UART_IRQHandler,                    // UART0/1 Overflow Interrupt Handler
    DMA0_0_IRQHandler,                  // DMA0 Interrupt Handler 0
    DMA0_1_IRQHandler,                  // DMA0 Interrupt Handler 1
    DMA1_0_IRQHandler,                  // DMA1 Interrupt Handler 0
    DMA1_1_IRQHandler,                  // DMA1 Interrupt Handler 1
    CGRA_IRQHandler,                    // CGRA Interrupt Handler
    TLX_IRQHandler                      // TLX Controller Interrupt Handler
};

// ----------------------------------------------------------------------------

void __attribute__ ((section(".after_vectors")))
Default_Handler(void)
{
#if defined(DEBUG)
__DEBUG_BKPT();
#endif
while (1)
  {
    ;
  }
}

// ----------------------------------------------------------------------------
