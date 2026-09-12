#ifndef ERR_ABORT_H
#define ERR_ABORT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static inline void err_exit(int code, const char *const errstr) {
    fputs(errstr, stderr);
    exit(code);
}

static inline void ferr_exit(int code, FILE *file,  const char *const errstr) {
    fputs(errstr, file);
    exit(code);
}

static inline void err_abort(const char *const errstr) {
    fputs(errstr, stderr);
    abort();
}

static inline void ferr_abort(FILE *file, const char *const errstr) {
    fputs(errstr, file);
    abort();
}

static inline void err_exit_fmt(int code, const char *const errfmt, ...) {
    va_list args;
    va_start(args, errfmt);
    vfprintf(stderr, errfmt, args);
    exit(code);
}

static inline void ferr_exit_fmt(int code, FILE *file, const char *const errfmt, ...) {
    va_list args;
    va_start(args, errfmt);
    vfprintf(file, errfmt, args);
    exit(code);
}

static inline void err_abort_fmt(const char *const errfmt, ...) {
    va_list args;
    va_start(args, errfmt);
    vfprintf(stderr, errfmt, args);
    abort();
}

static inline void ferr_abort_fmt(FILE *file, const char *const errfmt, ...) {
    va_list args;
    va_start(args, errfmt);
    vfprintf(file, errfmt, args);
    abort();
}

#endif
