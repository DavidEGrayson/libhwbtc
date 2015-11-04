use_c99()

# Settings for GCC
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
  # By default, symbols are not visible outside of the library.
  set (CMAKE_C_FLAGS "-fvisibility=hidden ${CMAKE_C_FLAGS}")

  # Don't warn about zero-length format strings.
  set (CMAKE_C_FLAGS "-Wno-format-zero-length ${CMAKE_C_FLAGS}")
endif ()

# Add the library and specify all of its source files.
add_library (hwbtc
  trezor.c
  error.c
)

set_target_properties(hwbtc PROPERTIES
  OUTPUT_NAME hwbtc-${LIBHWBTC_VERSION_MAJOR}
  SOVERSION ${LIBHWBTC_VERSION}
  VERSION ${LIBHWBTC_VERSION}
  DEFINE_SYMBOL LIBHWBTC_EXPORTS
)

include_directories (
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries (hwbtc hidapi)

configure_file (
  "libhwbtc_config.h.in"
  "libhwbtc_config.h"
)

configure_file (
  "info.rc.in"
  "info.rc"
)
