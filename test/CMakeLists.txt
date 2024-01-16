
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/tests")
set(MEMCHECK "valgrind")

add_library(doctest-main OBJECT
  "doctest.cpp"
)
target_compile_features(doctest-main PUBLIC cxx_std_20)

function(add_task_tests TASK_DIR TASK_NAME LIBRARIES)
  file(GLOB files "${TASK_DIR}/*.cpp")
  foreach(file ${files})
    get_filename_component(testcase ${file} NAME_WE)

    add_executable(${TASK_NAME}-${testcase})
    target_sources(${TASK_NAME}-${testcase}
      PRIVATE
        $<TARGET_OBJECTS:doctest-main> ${file}
    )
    target_include_directories(${TASK_NAME}-${testcase}
      PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    target_link_libraries(${TASK_NAME}-${testcase}
      PRIVATE
        ${LIBRARIES}
    )
    target_compile_features(${TASK_NAME}-${testcase} PUBLIC cxx_std_20)
    set_target_properties(${TASK_NAME}-${testcase} PROPERTIES
      LINKER_LANGUAGE CXX
    )

    add_test(NAME "${TASK_NAME}-${testcase}"
      COMMAND ${TASK_NAME}-${testcase}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    set_tests_properties("${TASK_NAME}-${testcase}" PROPERTIES LABELS TASK_NAME)

    if(RUN_VALGRIND_TESTS)
      add_test(NAME "${testcase}_valgrind"
        COMMAND ${MEMCHECK} ${CMAKE_CURRENT_BINARY_DIR}/${TASK_NAME}-${testcase}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      )
      set_tests_properties("${testcase}_valgrind" PROPERTIES LABELS "valgrind;${TASK_NAME}")
    endif()
  endforeach()
endfunction(add_task_tests)

add_task_tests("expr-ops" "expressions" "expr-ops")
add_task_tests("traverse" "traverse" "traversal")
