#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"

int
main(int argc, char* argv[])
{
  HAL_UNUSED(argc);
  HAL_UNUSED(argv);
  
  // Send a greeting to the trace device
  trace_printf("Hello, I am Amber!\r\n");

  return 0;
}
