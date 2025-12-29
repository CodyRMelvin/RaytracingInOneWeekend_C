cmake_minimum_required(VERSION 3.31)

set( CMAKE_C_COMPILER clang )

project(RaytracingIOW LANGUAGES C)

set( CMAKE_C_FLAGS "-Wall -Werror -Wextra" )
set( CMAKE_C_FLAGS_DEBUG "-O0 -g3" )
set( CMAKE_C_FLAGS_RELEASE "-O3" )
set( CMAKE_C_FLAGS_RELWITHDEBINFO "-O3 -g" )

add_subdirectory(src)

target_link_libraries( ${PROJECT_NAME} PRIVATE m )

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/)

target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Debug>:_DEBUG>")

set( CMAKE_C_STANDARD 23 )
target_compile_features( ${PROJECT_NAME} PUBLIC c_std_23 )

add_custom_target(
    run
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    DEPENDS ${PROJECT_NAME}
    USES_TERMINAL
)

