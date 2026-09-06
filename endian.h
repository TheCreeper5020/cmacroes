#ifndef ENDIAN_H
#define ENDIAN_H

#include <stdint.h>

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
    #define LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
    #define BIG_ENDIAN __ORDER_BIG_ENDIAN__
#else
    #define LITTLE_ENDIAN 1234
    #define BIG_ENDIAN 4321
#endif

static inline int cpu_endian(void) {
    #if defined(__BYTE_ORDER__)
        return __BYTE_ORDER__;
    #else
        uint32_t x = 0x11223344;
        unsigned char *p = (unsigned char*)(&x);
        return p[0] == 0x44 ? LITTLE_ENDIAN : BIG_ENDIAN;
    #endif
}

static inline uint64_t endian_reverse(uint64_t x) {
    return ((x << 56) & (0xFFull << 56))
        | ((x << 48) & (0xFFull << 48))
        | ((x << 40) & (0xFFull << 40))
        | ((x << 32) & (0xFFull << 32))
        | ((x << 24) & (0xFFull << 24))
        | ((x << 16) & (0xFFull << 16))
        | ((x << 8) & (0xFFull << 8))
        | (x & 0xFFull);
}

static inline uint64_t big_to_native(uint64_t x) {
    return cpu_endian() == BIG_ENDIAN ? x : endian_reverse(x);
}

static inline uint64_t little_to_native(uint64_t x) {
    return cpu_endian() == LITTLE_ENDIAN ? x : endian_reverse(x);
}

#endif
