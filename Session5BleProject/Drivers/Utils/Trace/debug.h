#ifndef DEBUG_H_
#define DEBUG_H_

#include "trace.h"
#include "stdio.h"

#ifdef DEBUG_SEMIHOSTING_PRINTF
#define PRINTF(...) trace_printf(__VA_ARGS__)
#define DEBUG(...) trace_printf(__VA_ARGS__)
#define DEBUG_LINE(fmt, ...) trace_printf(fmt "\r\n", ##__VA_ARGS__)
#else
#define PRINTF(...)
#define DEBUG(...)
#define DEBUG_LINE(...)
#endif

#endif /* DEBUG_H_ */
