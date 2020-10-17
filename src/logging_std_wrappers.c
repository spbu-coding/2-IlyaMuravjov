#include <stdarg.h>
#include <stdio.h>
#include <malloc.h>
#include "logging_std_wrappers.h"

int v_log_error(char *format, va_list args) {
    return vfprintf(stderr, format, args);
}

int log_error(char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = v_log_error(format, args);
    va_end(args);
    return result;
}

int logging_vscanf(char *format, int arg_count, va_list args) {
    int result = vscanf(format, args);
    if (result != arg_count) log_error("Unable to read from stdin\n");
    return result;
}

int logging_scanf(char *format, int arg_count, ...) {
    va_list args;
    va_start(args, arg_count);
    int result = logging_vscanf(format, arg_count, args);
    va_end(args);
    return result;
}

void *logging_malloc(size_t block_size) {
    void *allocated_block = malloc(block_size);
    if (!allocated_block) log_error("Unable to allocate memory\n");
    return allocated_block;
}
