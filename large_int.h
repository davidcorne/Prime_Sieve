#include <stdint.h>

// give back the correct large unsigned integer for 32/64 bit
#if INTPTR_MAX == INT32_MAX
#define LARGE_INT uint32_t
#elif INTPTR_MAX == INT64_MAX
#define LARGE_INT uint64_t
#else
    #error "Environment not 32 or 64-bit."
#endif
