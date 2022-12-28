
add_library(expr-ops)
target_sources(expr-ops
  PRIVATE
    ExprOps.cpp
)

target_include_directories(expr-ops
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(expr-ops
  PUBLIC
    expr-tree
)

target_compile_features(expr-ops PUBLIC cxx_std_20)
set_target_properties(expr-ops
  PROPERTIES
  LINKER_LANGUAGE CXX
)

