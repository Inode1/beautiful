enable_testing ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -O3 -Wall -Wextra -pedantic")

include(CMakeParseArguments)

add_custom_target(unit_test)
function(add_unit_test dependency)
    cmake_parse_arguments(UT "" "NAME" "COMMAND" ${ARGN} )
    add_test(${ARGN})
    add_dependencies(unit_test ${dependency})
    message(STATUS "Dependency ${dependency}")
    set_target_properties(
        ${dependency}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
    )
endfunction(add_unit_test)

add_executable(test_bruteforce test_bruteforce.cpp)
add_unit_test(test_bruteforce NAME test_bruteforce COMMAND $<TARGET_FILE:test_bruteforce>)

add_custom_command(
     TARGET unit_test
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND ${CMAKE_CTEST_COMMAND} --verbose -C $<CONFIGURATION> ${CMAKE_BINARY_DIR}/test
)