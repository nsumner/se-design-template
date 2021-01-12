
add_library(expr-ops
  ExprOps.cpp
)

target_include_directories(expr-ops
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(expr-ops
  expr-tree
)

set_target_properties(expr-ops
  PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
)

