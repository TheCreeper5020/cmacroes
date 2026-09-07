#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#ifdef __BYTE_ORDER__
    #define ENDIAN_LITTLE __ORDER_LITTLE_ENDIAN__
    #define ENDIAN_BIG __ORDER_BIG_ENDIAN__
#else
    #define ENDIAN_LITTLE 1234
    #define ENDIAN_BIG 4321
#endif

static inline int cpu_endian(void) {
    #ifdef __BYTE_ORDER__
        return __BYTE_ORDER__;
    #else
        uint32_t x = 0x11223344;
        unsigned char *p = (unsigned char*)(&x);
        return p[0] == 0x44 ? ENDIAN_LITTLE : ENDIAN_BIG;
    #endif // defined(__BYTE_ORDER__)
}

static inline uint16_t byte_reverse_16(uint16_t x) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_bswap16(x);
#else
    return ((x & 0x00FF) << 8)
        |  ((x & 0xFF00) >> 8);
#endif // defined(__GNUC__) || defined(__clang__)
}

static inline uint32_t byte_reverse_32(uint32_t x) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_bswap32(x);
#else
    return ((x & 0x000000FF) << 24)
        |  ((x & 0x0000FF00) <<  8)
        |  ((x & 0x00FF0000) >>  8)
        |  ((x & 0xFF000000) >> 24);
#endif // defined(__GNUC__) || defined(__clang__)
}

static inline uint64_t byte_reverse_64(uint64_t x) {
#if defined(__GNUC__) || defined(__clang__)
    return  __builtin_bswap64(x);
#else
    return ((x & 0x00000000000000FF) << 56)
        |  ((x & 0x000000000000FF00) << 40)
        |  ((x & 0x0000000000FF0000) << 24)
        |  ((x & 0x00000000FF000000) <<  8)
        |  ((x & 0x000000FF00000000) >>  8)
        |  ((x & 0x0000FF0000000000) >> 24)
        |  ((x & 0x00FF000000000000) >> 40)
        |  ((x & 0xFF00000000000000) >> 56);
#endif // defined(__GNUC__) || defined(__clang__)
}

static inline uintmax_t byte_reverse_max(uintmax_t x, size_t byte_count) {
    assert(byte_count <= sizeof(uintmax_t));
    switch (byte_count) {
        case 1:
            return x;
        case 2:
            return byte_reverse_16(x);
        case 4:
            return byte_reverse_32(x);
        case 8:
            return byte_reverse_64(x);
        default: {
            uintmax_t accum = 0;
            for (size_t i = 0; i < byte_count; i++) {
                uintmax_t curr_byte = (x >> (i * 8)) & 0xFF;
                uintmax_t byte_shift = byte_count - i - 1;
                accum |= curr_byte << (8 * byte_shift);
            }
            return accum;
        }
    }
}

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
#define byte_reverse(x) \
    (typeof_unqual(x))(_Generic((x), \
        uint8_t: (x), \
        uint16_t: byte_reverse_16(x), \
        uint32_t: byte_reverse_32(x), \
        uint64_t: byte_reverse_64(x), \
        default: byte_reverse_max(x, sizeof(x)) \
    ))
#else
#define byte_reverse(x) (_Generic((x), \
        uint8_t: (x), \
        uint16_t: byte_reverse_16(x), \
        uint32_t: byte_reverse_32(x), \
        uint64_t: byte_reverse_64(x), \
        default: byte_reverse_max(x, sizeof(x)) \
    ))
#endif

#if defined(__BYTE_ORDER__)
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define big_to_native(x) (x)
#define little_to_native(x) (byte_reverse(x))
#else
#define big_to_native(x) (byte_reverse(x))
#define little_to_native(x) (x)
#endif // __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#else
#define big_to_native(x) (cpu_endian() == ENDIAN_BIG ? (x) : byte_reverse(x))
#define little_to_native(x) (cpu_endian() == ENDIAN_LITTLE ? (x) : byte_reverse(x))
#endif // defined(__BYTE_ORDER__)

#endif // defined(ENDIANNESS_H)
