#include "amberm3vx.h"
#include "amberm3vx_hal.h"

#include "diag/trace.h"

#if defined(USE_FULL_ASSERT)
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void
assert_failed (uint8_t* file, uint32_t line)
{
  // Change to a custom implementation to report the file name and line number.
  trace_printf("Wrong parameters value: file %s on line %d\r\n", file, line);

  // Infinite loop
  while (1)
  {
    ;
  }
}
#endif
