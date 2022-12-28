
add_library(traversal)
target_sources(traversal
  PRIVATE
    empty.cpp
)

target_include_directories(traversal
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(traversal
  PUBLIC
    expr-tree
)

target_compile_features(traversal PUBLIC cxx_std_20)
set_target_properties(traversal PROPERTIES
  LINKER_LANGUAGE CXX
)

