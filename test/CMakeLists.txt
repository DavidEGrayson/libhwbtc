include (CheckIncludeFileCXX)

# If catch.hpp is not present, we want to simply skip compiling the
# tests.  This allows someone to compile and install the library
# without having catch installed.  The header can either be installed
# in this directory or in a standard system location.
set (CMAKE_REQUIRED_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}")
CHECK_INCLUDE_FILE_CXX (catch.hpp HAVE_CATCH_FRAMEWORK)
if (NOT HAVE_CATCH_FRAMEWORK)
  message (STATUS "The test suite will not be built.")
  return ()
endif ()

use_cxx11()

file(GLOB test_sources *.cpp)

add_executable(run_test ${test_sources})

set_target_properties(run_test PROPERTIES
  LINK_FLAGS "${link_flags}"
)

include_directories (
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/src"
  "${CMAKE_BINARY_DIR}/src"
)

target_link_libraries(run_test hwbtc)
