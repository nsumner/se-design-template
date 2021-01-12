cmake_minimum_required(VERSION 3.13)
project(CMPT745-ex01-design)

set(PACKAGE_NAME CMPT745-ex01-design)
set(PACKAGE_VERSION 0.2)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "wsumner@sfu.ca")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(
  "$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-fno-rtti;-Wall>"
  "$<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:DEBUG>>:-fno-omit-frame-pointer;-O0;-g;-fsanitize=address,undefined>"
)
add_link_options(
  "$<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:DEBUG>>:-fsanitize=address,undefined>"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/out/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/out/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/out/lib")

add_subdirectory(lib)

include(CTest)

if (BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
