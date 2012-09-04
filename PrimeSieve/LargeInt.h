#include <stdint.h>

// give back the correct large unsigned integer for 32/64 bit
#ifdef UINT64_MAX
  #define LARGE_INT uint64_t
#elif
  #ifdef UINT32_MAX
    #define LARGE_INT uint32_t
    #error "32 bit"
  #endif
#else
  #error "Environment not 32 or 64-bit."
#endif
