#pragma once

#include <stdint.h>
#include <stdbool.h>

enum libhwbtc_error_code
{
    LIBHWBTC_ERROR_MEMORY = 1,
};

typedef struct libhwbtc_error libhwbtc_error;

bool libhwbtc_error_has_code(const libhwbtc_error * error, uint32_t code);
const char * libhwbtc_error_get_message(const libhwbtc_error * error);

