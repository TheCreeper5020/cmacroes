#ifndef BIT_MANIP_H
#define BIT_MANIP_H

#include <limits.h>
#include <stddef.h>
#include <stdbool.h>

#define BYTE_COUNT(bit_count) (size_t)(((bit_count) + CHAR_BIT - 1) / CHAR_BIT)
#define BIT_COUNT(byte_count) (size_t)((byte_count) * CHAR_BIT)
#define BITSET(name, bit_count) unsigned char name[BYTE_COUNT(bit_count)]
#define BITSET_BIT_COUNT(bitset) (BIT_COUNT(sizeof(bitset)))

static inline bool bit_get(const unsigned char *bitset, size_t index) {
    size_t byte_index = index / CHAR_BIT;
    size_t bit_in_byte = index % CHAR_BIT;
    size_t mask = 1 << bit_in_byte;
    return (bitset[byte_index] & mask) != 0;
}

static inline void bit_set(unsigned char *bitset, size_t index) {
    size_t byte_index = index / CHAR_BIT;
    size_t bit_in_byte = index % CHAR_BIT;
    size_t mask = (size_t)(1) << bit_in_byte;
    bitset[byte_index] |= mask;
}

static inline void bit_clr(unsigned char *bitset, size_t index) {
    size_t byte_index = index / CHAR_BIT;
    size_t bit_in_byte = index % CHAR_BIT;
    size_t mask = 1 << bit_in_byte;
    bitset[byte_index] &= ~mask;
}

static inline bool bit_flip(unsigned char *bitset, size_t index) {
    size_t byte_index = index / CHAR_BIT;
    size_t bit_in_byte = index % CHAR_BIT;
    size_t mask = 1 << bit_in_byte;
    bitset[byte_index] ^= mask;
    return bit_get(bitset, index);
}

static inline void bit_set_range(unsigned char *bitset, size_t start, size_t count) {
    for (size_t i = start; i < start + count; i++) {
        bit_set(bitset, i);
    }
}

static inline void bit_clr_range(unsigned char *bitset, size_t start, size_t count) {
    for (size_t i = start; i < start + count; i++) {
         bit_clr(bitset, i);
    }
}

static inline size_t bit_flip_range(unsigned char *bitset, size_t start, size_t count) {
    size_t num_flipped = 0;
    for (size_t i = start; i < start + count; i++) {
        num_flipped += bit_flip(bitset, i);
    }
    return num_flipped;
}

static inline size_t popcnt(unsigned char *bitset, size_t size) {
    size_t count = 0;
    for (size_t i = 0; i < BIT_COUNT(size); i++) {
        count += bit_get(bitset, i);
    }
    return count;
}

#endif
