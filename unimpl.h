#ifndef UNIMPL_H
#define UNIMPL_H

#ifdef __cplusplus

#include <cstdlib>
#include <cstdio>

#define unimplemented() do { \
    std::fprintf(stderr, "%s(): Function not implemented (line %d in file %s).\n", __func__, __LINE__, __FILE__);\
    std::abort();\
} while (0)

#else

#include <stdlib.h>
#include <stdio.h>

#define unimplemented() do { \
    fprintf(stderr, "%s(): Function not implemented (line %d in file %s).\n", __func__, __LINE__, __FILE__);\
    abort();\
} while (0)

#endif

#endif
