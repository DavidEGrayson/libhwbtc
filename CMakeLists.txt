cmake_minimum_required (VERSION 2.8)
project (libhwbtc)

option (BUILD_SHARED_LIBS "Build as shared library" TRUE)

# Our C code uses features from the C99 standard.
macro(use_c99)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_C_FLAGS "--std=gnu99 ${CMAKE_C_FLAGS}")
    endif ()
  else ()
    set (CMAKE_C_STANDARD 99)
  endif ()
endmacro(use_c99)

# Our C++ code uses features from the C++11 standard.
macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_C_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

set (LIBHWBTC_VERSION_MAJOR 1)
set (LIBHWBTC_VERSION_MINOR 0)
set (LIBHWBTC_VERSION_PATCH 0)

set (LIBHWBTC_VERSION ${LIBHWBTC_VERSION_MAJOR}.${LIBHWBTC_VERSION_MINOR}.${LIBHWBTC_VERSION_PATCH})

# Put libraries and executables in the top level of the bin directory
# so that the executables can find the libraries and it is easy to run
# everything.
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Settings for GCC
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
  # Warn about everything.
  set (CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS}")
endif ()

if (WIN32)

  # Enable correct behavior for the return value of vsnprintf.
  add_definitions (-D__USE_MINGW_ANSI_STDIO=1)

endif ()

add_subdirectory (src)
add_subdirectory (cli)
add_subdirectory (test)
