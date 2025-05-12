cmake_minimum_required(VERSION 3.27)
project(RaylibExamples LANGUAGES C CXX)

# Compiler standards
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile_commands.json for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Optional: only build selected examples
option(BUILD_ONLY "Regex to match example filenames to build only specific targets" "")

if(BUILD_ONLY)
    message(STATUS "BUILD_ONLY is set to '${BUILD_ONLY}' — only matching example targets will be built")
endif()

# Debug info format for MSVC
if(MSVC)
    if(USE_HOTRELOAD)
        set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "EditAndContinue")  # /ZI
    else()
        set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "ProgramDatabase")  # /Zi
    endif()
endif()

# Global output dir for all executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Fetch raylib 5.5
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# === Build one .exe per source file ===
file(GLOB_RECURSE EXAMPLE_SOURCES CONFIGURE_DEPENDS examples/*.c examples/*.cpp)

foreach(SRC_FILE IN LISTS EXAMPLE_SOURCES)
    # Normalize path separators and get relative path
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}/examples" "${SRC_FILE}")
    file(TO_CMAKE_PATH "${REL_PATH}" REL_PATH)

    # Convert to a valid target name: e.g., core_basic_window
    string(REPLACE "/" "_" TARGET_NAME "${REL_PATH}")
    string(REPLACE "\\" "_" TARGET_NAME "${TARGET_NAME}")
    string(REPLACE ".c" "" TARGET_NAME "${TARGET_NAME}")
    string(REPLACE ".cpp" "" TARGET_NAME "${TARGET_NAME}")

    # Optional: skip unmatched targets
    if(BUILD_ONLY AND NOT TARGET_NAME MATCHES "${BUILD_ONLY}")
        message(STATUS "Skipping target '${TARGET_NAME}' (filtered by BUILD_ONLY)")
        continue()
    endif()

    # Extract top-level folder under examples/, e.g., "core"
    get_filename_component(FOLDER_NAME "${REL_PATH}" DIRECTORY)
    string(REGEX MATCH "^[^/]+" GROUP "${FOLDER_NAME}")

    message(STATUS "Creating target '${TARGET_NAME}' from '${SRC_FILE}' in group '${GROUP}'")

    add_executable(${TARGET_NAME} ${SRC_FILE})
    target_link_libraries(${TARGET_NAME} PRIVATE raylib)

    # Set logical folder in Visual Studio Solution Explorer
    set_target_properties(${TARGET_NAME} PROPERTIES
        FOLDER "Raylib/${GROUP}"
    )

    # Optional ASan support for MSVC
    if(MSVC AND NOT USE_HOTRELOAD)
        target_compile_options(${TARGET_NAME} PRIVATE
            $<$<CONFIG:Debug>:/DDEBUG /Zi /Od /RTC1 /fsanitize=address>
        )
        target_link_options(${TARGET_NAME} PRIVATE
            $<$<CONFIG:Debug>:/INFERASANLIBS /INCREMENTAL>
        )
    endif()
endforeach()