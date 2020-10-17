#include <memory.h>
#include <malloc.h>
#include <stdio.h>
#include "logging_std_wrappers.h"
#include "sort.h"

static const int TOO_FEW_ARGS_ERROR_CODE = -1;
static const int TOO_MANY_ARGS_ERROR_CODE = -2;
static const int ARG_DUPLICATION_ERROR_CODE = -3;
static const int NO_VALID_ARGS_ERROR_CODE = -4;

static const int MALLOC_ERROR_CODE = -10;
static const int SCANF_ERROR_CODE = -11;
static const int FPRINTF_ERROR_CODE = -12;

static const size_t INPUT_ARRAY_MAX_LENGTH = 100;

struct long_long_range_t {
    long long *from;
    long long *to;
};

void destroy_long_long_range(struct long_long_range_t *range) {
    if (range->from) free(range->from);
    if (range->to) free(range->to);
}

int string_starts_with(char *string, char *prefix) {
    return strncmp(string, prefix, strlen(prefix)) == 0;
}

int process_command_line_args(int argc, char **argv, struct long_long_range_t *range) {
    argv++, argc--; // ignore the name of the program
    if (argc < 1) return TOO_FEW_ARGS_ERROR_CODE;
    if (argc > 2) return TOO_MANY_ARGS_ERROR_CODE;
    for (int i = 0; i < argc; i++) {
        char *equal_sign_in_current_arg = strchr(argv[i], '=');
        long long number = equal_sign_in_current_arg ? strtoll(equal_sign_in_current_arg + 1, NULL, 0) : 0;
        if (string_starts_with(argv[i], "--from=")) {
            if (range->from) return ARG_DUPLICATION_ERROR_CODE;
            range->from = logging_malloc(sizeof(long long));
            if (!range->from) return MALLOC_ERROR_CODE;
            *range->from = number;
        } else if (string_starts_with(argv[i], "--to=")) {
            if (range->to) return ARG_DUPLICATION_ERROR_CODE;
            range->to = logging_malloc(sizeof(long long));
            if (!range->to) return MALLOC_ERROR_CODE;
            *range->to = number;
        }
    }
    if (!range->from && !range->to) return NO_VALID_ARGS_ERROR_CODE;
    return 0;
}

int read_reduced_input_array(long long *arr, size_t *arr_length, size_t arr_max_length, struct long_long_range_t *range) {
    char delimiter;
    long long elm;
    *arr_length = 0;
    do {
        if (logging_scanf("%lld%c", 2, &elm, &delimiter) != 2)
            return SCANF_ERROR_CODE;
        int is_elm_valid = 1;
        if (range->from && elm <= *range->from) {
            if (fprintf(stdout, "%lld ", elm) < 0) return FPRINTF_ERROR_CODE;
            is_elm_valid = 0;
        }
        if (range->to && elm >= *range->to) {
            if (fprintf(stderr, "%lld ", elm) < 0) return FPRINTF_ERROR_CODE;
            is_elm_valid = 0;
        }
        if (is_elm_valid) {
            arr[*arr_length] = elm;
            (*arr_length)++;
        }
    } while (delimiter == ' ' && *arr_length < arr_max_length);
    return 0;
}

size_t count_differences(long long *arr_1, long long *arr_2, size_t arr_length) {
    size_t result = 0;
    for (size_t i = 0; i < arr_length; i++)
        if (arr_1[i] != arr_2[i])
            result++;
    return result;
}

int main(int argc, char **argv) {
    struct long_long_range_t range = {NULL, NULL};
    int args_processing_result = process_command_line_args(argc, argv, &range);
    if (args_processing_result != 0) {
        destroy_long_long_range(&range);
        return args_processing_result;
    }
    long long arr[INPUT_ARRAY_MAX_LENGTH];
    size_t arr_length;
    int reading_array_result = read_reduced_input_array(arr, &arr_length, INPUT_ARRAY_MAX_LENGTH, &range);
    destroy_long_long_range(&range);
    if (reading_array_result != 0) return reading_array_result;
    long long arr_copy[INPUT_ARRAY_MAX_LENGTH];
    memcpy(arr_copy, arr, arr_length * sizeof(long long));
    sort(arr_copy, arr_length);
    return count_differences(arr, arr_copy, arr_length);
}
