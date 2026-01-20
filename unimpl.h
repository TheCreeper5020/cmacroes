#ifndef UNIMPL_H
#define UNIMPL_H

#include <stdlib.h>
#include <stdio.h>

#define unimplemented() do { \
    fprintf(stderr, "%s(): Function not implemented.\n", __func__);\
    abort();\
} while (0)

#endif
