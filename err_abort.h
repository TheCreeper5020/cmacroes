#ifndef ERR_ABORT_H
#define ERR_ABORT_H

#include <stdio.h>
#include <stdlib.h>

#define exit_err(err, code) do { \
    fputs(err, stderr); \
    exit(code); \
} while (0)

#define abort_err(err) do { \
    fputs(err, stderr); \
    abort(); \
} while (0)

#endif
