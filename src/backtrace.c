#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>

#define  array_size        (1 << 7)
void DebugBacktrace(int signo) 
{
  void *array[array_size];
  size_t frames;

  frames = backtrace(array, array_size);
  fprintf(stderr, "Error: signal %d:\n", signo);
  backtrace_symbols_fd(array, frames, STDERR_FILENO);

  exit(1);
}
