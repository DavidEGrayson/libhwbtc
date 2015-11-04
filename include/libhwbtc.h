#pragma once

/*! The major component of this library's version number.  In
 * accordance with semantic versioning, this gets incremented every
 * time there is a breaking change. */
#define LIBHWBTC_VERSION_MAJOR 1

#include <stdint.h>
#include <stdbool.h>

enum libhwbtc_error_code
{
    LIBHWBTC_ERROR_MEMORY = 1,
};

typedef struct libhwbtc_error libhwbtc_error;

#ifdef _WIN32
#  define LIBHWBTC_DLL_EXPORT __declspec(dllexport)
#  define LIBHWBTC_DLL_IMPORT __declspec(dllimport)
#else
#  define LIBHWBTC_DLL_IMPORT __attribute__((visibility ("default")))
#  define LIBHWBTC_DLL_EXPORT __attribute__((visibility ("default")))
#endif

#define LIBHWBTC_WARN_UNUSED __attribute__((warn_unused_result))

#ifdef LIBHWBTC_STATIC
#  define LIBHWBTC_API
#else
#  ifdef LIBHWBTC_EXPORTS
#    define LIBHWBTC_API LIBHWBTC_DLL_EXPORT
#  else
#    define LIBHWBTC_API LIBHWBTC_DLL_IMPORT
#  endif
#endif

LIBHWBTC_API
bool libhwbtc_error_has_code(const libhwbtc_error * error, uint32_t code);

LIBHWBTC_API
const char * libhwbtc_error_get_message(const libhwbtc_error * error);

LIBHWBTC_API
void libhwbtc_error_free(libhwbtc_error * error);

LIBHWBTC_API
libhwbtc_error * libhwbtc_error_copy(const libhwbtc_error * src_error);
