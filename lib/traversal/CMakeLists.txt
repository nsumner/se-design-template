
add_library(traversal
  empty.cpp
)

target_include_directories(traversal
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(traversal
  expr-tree
)

set_target_properties(traversal PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

