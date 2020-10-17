#ifndef TASK_2_LOGGING_STD_WRAPPERS_H
#define TASK_2_LOGGING_STD_WRAPPERS_H

#include <stdarg.h>

int v_log_error(char *format, va_list args);
int log_error(char *format, ...);
int logging_vscanf(char *format, int arg_count, va_list args);
int logging_scanf(char *format, int arg_count, ...);
void *logging_malloc(size_t block_size);

#endif // TASK_2_LOGGING_STD_WRAPPERS_H
