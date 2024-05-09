cmake_minimum_required (VERSION 3.29.2)
project ("SnakeGameC")

if (POLICY CMP0076)
	cmake_policy (SET CMP0076 NEW)
endif ()

set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_RC_CREATE_STATIC_LIBRARY 1)
set (CONTROLLER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/controller")

file (GLOB_RECURSE CONTROLLER_SOURCES "${CONTROLLER_PATH}/*.c")
file (GLOB_RECURSE CONTROLLER_HEADERS "${CONTROLLER_PATH}/*.h")
add_library (controller ${CONTROLLER_SOURCES} ${CONTROLLER_HEADERS})
target_include_directories (controller PUBLIC "src/controller")

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/snake.res
    COMMAND windres -i \"${CMAKE_CURRENT_SOURCE_DIR}/src/resources/snake.rc\"
                    -O coff -o \"${CMAKE_CURRENT_BINARY_DIR}/snake.res\"
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/snake.rc
    COMMENT "Compiling resource file"
)
add_custom_target(
    resources
    ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/snake.res
)

add_executable (snake "src/main.c")
add_dependencies(snake resources)
set_target_properties (snake PROPERTIES LINK_FLAGS \"${CMAKE_CURRENT_BINARY_DIR}/snake.res\")
target_link_libraries (snake controller)