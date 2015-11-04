#pragma once
#include <libhwbtc.h>

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#ifdef NDEBUG
#define TEST_API
#else
#define TEST_API LIBHWBTC_API
#endif

TEST_API
libhwbtc_error * error_create(const char * format, ...);

TEST_API
libhwbtc_error * error_add(libhwbtc_error * error, const char * format, ...);

TEST_API
libhwbtc_error * error_add_code(libhwbtc_error * error, uint32_t code);

TEST_API
extern libhwbtc_error error_no_memory;
