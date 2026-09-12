#ifndef UNIMPL_H
#define UNIMPL_H

#include <stdlib.h>
#include <stdio.h>

#define unimplemented() do {\
    fprintf(stderr, "%s(): Function not implemented (line %d in file %s).\n", __func__, __LINE__, __FILE__);\
    abort();\
} while (0)

#define todo() do {\
    fprintf(stderr, "TODO! (line %d in function %s() in file %s)\n", __LINE__, __func__, __FILE__);\
    abort();\
} while (0)

#endif
