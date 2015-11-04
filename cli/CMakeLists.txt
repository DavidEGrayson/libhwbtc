use_cxx11()

add_executable(hwbtccli cli.cpp)

include_directories (
  "${CMAKE_SOURCE_DIR}/include"
)

# tmphax
target_link_libraries (hwbtccli hidapi)
