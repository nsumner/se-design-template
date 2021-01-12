
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/out/test")
set(MEMCHECK "valgrind")

add_library(doctest-main OBJECT
  "doctest.cpp"
)

function(add_task_tests TASK_DIR TASK_NAME LIBRARIES)
  file(GLOB files "${TASK_DIR}/*.cpp")
  foreach(file ${files})
    get_filename_component(testcase ${file} NAME_WE)

    add_executable(${testcase} $<TARGET_OBJECTS:doctest-main> ${file})
    target_include_directories(${testcase} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    target_link_libraries(${testcase} ${LIBRARIES})
    set_target_properties(${testcase} PROPERTIES
      LINKER_LANGUAGE CXX
      CXX_STANDARD 20
    )

    add_test(NAME "${testcase}"
      COMMAND ${testcase}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    set_tests_properties("${testcase}" PROPERTIES LABELS TASK_NAME)

    if(RUN_VALGRIND_TESTS)
      add_test(NAME "${testcase}_valgrind"
        COMMAND ${MEMCHECK} ${CMAKE_CURRENT_BINARY_DIR}/${testcase}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      )
      set_tests_properties("${testcase}_valgrind" PROPERTIES LABELS "valgrind;${TASK_NAME}")
    endif()
  endforeach()
endfunction(add_task_tests)

add_task_tests("expr-ops" "Expressions" "expr-ops")
add_task_tests("traverse" "Traversal" "traversal")
