cmake_minimum_required (VERSION 3.29.2)
project ("SnakeGameC")

set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_RC_CREATE_STATIC_LIBRARY 1)
set (SOURCES_PATH "src")
set (RESOURCES_FILE "src/resources/snake.rc")
set (MAIN_FILE "src/main.c")
set (SETTINGS_FILE "src/settings.ini")

get_filename_component (MAIN_FILE_ABS ${MAIN_FILE} ABSOLUTE)
get_filename_component (RESOURCES_FILE ${RESOURCES_FILE} ABSOLUTE)
get_filename_component (RESOURCES_FILE_NAME ${RESOURCES_FILE} NAME_WE)
set (RESOURCES_FILE_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_FILE_NAME}.res")

if (POLICY CMP0076)
	cmake_policy (SET CMP0076 NEW)
endif ()

file (GLOB_RECURSE SOURCES_FILES "${SOURCES_PATH}/*.c")
file (GLOB_RECURSE SOURCES_HEADERS "${SOURCES_PATH}/*.h")
list (REMOVE_DUPLICATES SOURCES_FILES)
list (REMOVE_ITEM SOURCES_FILES ${MAIN_FILE_ABS})
list (REMOVE_DUPLICATES SOURCES_HEADERS)
add_library (sources ${SOURCES_FILES} ${SOURCES_HEADERS})

set (SOURCES_HEADERS_DIRS)
foreach (HEADER ${SOURCES_HEADERS})
	get_filename_component (DIR_PATH ${HEADER} DIRECTORY)
	list (APPEND SOURCES_HEADERS_DIRS ${DIR_PATH})
endforeach ()
list (REMOVE_DUPLICATES SOURCES_HEADERS_DIRS)
target_include_directories (sources PUBLIC ${SOURCES_HEADERS_DIRS})

add_custom_command (
	OUTPUT ${RESOURCES_FILE_OUTPUT}
	COMMAND windres -i \"${RESOURCES_FILE}\" -O coff -o \"${RESOURCES_FILE_OUTPUT}\"
	DEPENDS ${RESOURCES_FILE}
	COMMENT "Compiling resource file"
)
add_custom_target(
	resources
	ALL
	DEPENDS ${RESOURCES_FILE_OUTPUT}
)

file (COPY ${SETTINGS_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable (snake ${MAIN_FILE})
target_link_libraries (snake PRIVATE sources)
add_dependencies (snake resources)
set_target_properties (snake PROPERTIES LINK_FLAGS \"${RESOURCES_FILE_OUTPUT}\")