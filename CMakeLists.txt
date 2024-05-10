cmake_minimum_required (VERSION 3.28)
project ("SnakeGameC")

# --------
#  CONSTS
# --------

set (SOURCES_PATH "src")
set (RESOURCES_FILE "src/resources/snake.rc")
set (MAIN_FILE "src/main.c")
set (SETTINGS_FILE "src/config.ini")
#set (CMAKE_MESSAGE_LOG_LEVEL DEBUG)

# -----------------------------------------------------------
#  DO NOT CHANGE CODE BELLOW IF YOU ARE NOT SURE WHAT YOU DO
# -----------------------------------------------------------

message (STATUS "Configuring the project...")
set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_RC_CREATE_STATIC_LIBRARY ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (POLICY CMP0076)
	cmake_policy (SET CMP0076 NEW)
endif ()
message (STATUS "Configuring the project... Done!")

message (STATUS "Generating variables...")
get_filename_component (MAIN_FILE_ABS ${MAIN_FILE} ABSOLUTE)
get_filename_component (RESOURCES_FILE_ABS ${RESOURCES_FILE} ABSOLUTE)
get_filename_component (RESOURCES_FILE_NAME_WE ${RESOURCES_FILE} NAME_WE)
set (RESOURCES_FILE_OUTPUT_ABS "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_FILE_NAME_WE}.res")
message (STATUS "Generating variables... Done!")

message (DEBUG "[CONST] SOURCES_PATH = ${SOURCES_PATH}")
message (DEBUG "[CONST] RESOURCES_FILE = ${RESOURCES_FILE}")
message (DEBUG "[GEN] RESOURCES_FILE_ABS = ${RESOURCES_FILE_ABS}")
message (DEBUG "[GEN] RESOURCES_FILE_NAME_WE = ${RESOURCES_FILE_NAME_WE}")
message (DEBUG "[GEN] RESOURCES_FILE_OUTPUT_ABS = ${RESOURCES_FILE_OUTPUT_ABS}")
message (DEBUG "[CONST] MAIN_FILE = ${MAIN_FILE}")
message (DEBUG "[GEN] MAIN_FILE_ABS = ${MAIN_FILE_ABS}")
message (DEBUG "[CONST] SETTINGS_FILE = ${MAIN_FILE}")

message (STATUS "Creating sources library...")
file (GLOB_RECURSE SOURCES_FILES "${SOURCES_PATH}/*.c")
file (GLOB_RECURSE SOURCES_HEADERS "${SOURCES_PATH}/*.h")
list (REMOVE_DUPLICATES SOURCES_FILES)
list (REMOVE_ITEM SOURCES_FILES ${MAIN_FILE_ABS})
list (REMOVE_DUPLICATES SOURCES_HEADERS)
add_library (sources ${SOURCES_FILES} ${SOURCES_HEADERS})
message (STATUS "Creating sources library... Done!")

message (DEBUG "[GEN] SOURCES_FILES = ${SOURCES_FILES}")
message (DEBUG "[GEN] SOURCES_HEADERS = ${SOURCES_HEADERS}")

message (STATUS "Including headers directories...")
set (SOURCES_HEADERS_DIRS)
foreach (HEADER ${SOURCES_HEADERS})
	get_filename_component (DIR_PATH ${HEADER} DIRECTORY)
	list (APPEND SOURCES_HEADERS_DIRS ${DIR_PATH})
endforeach ()
list (REMOVE_DUPLICATES SOURCES_HEADERS_DIRS)
target_include_directories (sources PUBLIC ${SOURCES_HEADERS_DIRS})
message (STATUS "Including headers directories... Done!")

message (DEBUG "[GEN] SOURCES_HEADERS_DIRS = ${SOURCES_HEADERS_DIRS}")

message (STATUS "Creating custom command and target to compile resource file...")
add_custom_command (
	OUTPUT ${RESOURCES_FILE_OUTPUT_ABS}
	COMMAND windres -i \"${RESOURCES_FILE_ABS}\" -O coff -o \"${RESOURCES_FILE_OUTPUT_ABS}\"
	DEPENDS ${RESOURCES_FILE_ABS}
	COMMENT "Compiling resource file..."
)
add_custom_target(
	resources
	ALL
	DEPENDS ${RESOURCES_FILE_OUTPUT_ABS}
)
message (STATUS "Creating custom command and target to compile resource file... Done!")

message (STATUS "Copying settings file...")
message (DEBUG "[CMAKE] CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
file (COPY ${SETTINGS_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message (STATUS "Copying settings file... Done!")

message (STATUS "Creating executable...")
add_executable (snake ${MAIN_FILE})
message (STATUS "Creating executable... Done!")

message (STATUS "Linking sources library...")
target_link_libraries (snake PRIVATE sources)
message (STATUS "Linking sources library... Done!")

message (STATUS "Compiling resources...")
add_dependencies (snake resources)
message (STATUS "Compiling resources... Done!")

message (STATUS "Configuring linking flags...")
set_target_properties (snake PROPERTIES LINK_FLAGS \"${RESOURCES_FILE_OUTPUT_ABS}\")
message (STATUS "Configuring linking flags... Done!")