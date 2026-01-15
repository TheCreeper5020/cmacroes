#ifndef unimplemented
#define unimplemented() do { \
    fprintf(stderr, "%s(): Function not implemented.\n", __func__);\
    abort();\
} while (0)
#endif
