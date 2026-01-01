cmake_minimum_required(VERSION 3.27)
project(gramarye-components C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# WebAssembly toggle
option(BUILD_WEB "Build with Emscripten (WebAssembly)" OFF)

if(EMSCRIPTEN OR BUILD_WEB)
    set(PLATFORM Web CACHE STRING "" FORCE)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# Option to build as shared or static (default static)
option(BUILD_SHARED_LIBS "Build shared library" OFF)

# ============================================================================
# Dynamic Component Folder Selection
# ============================================================================
# This system allows you to selectively build component folders.
# 
# Usage examples:
#   1. Build all folders (default):
#      cmake ..
# 
#   2. Build specific folders via list:
#      cmake -DCOMPONENTS_FOLDERS="core;textures;tilemap" ..
# 
#   3. Disable all, then enable specific ones:
#      cmake -DBUILD_COMPONENTS_ALL=OFF -DBUILD_COMPONENTS_CORE=ON -DBUILD_COMPONENTS_TEXTURES=ON ..
# 
#   4. For a 2D game, exclude 3D components:
#      cmake -DCOMPONENTS_FOLDERS="core;textures;tilemap" ..  # excludes "3d" folder if it exists
#
# Discover available component folders
file(GLOB COMPONENT_FOLDERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/src/*")
list(FILTER COMPONENT_FOLDERS INCLUDE REGEX "^[^/]+$")  # Only top-level directories
# Filter out files and keep only directories
set(VALID_COMPONENT_FOLDERS "")
foreach(FOLDER ${COMPONENT_FOLDERS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/${FOLDER}")
        list(APPEND VALID_COMPONENT_FOLDERS ${FOLDER})
    endif()
endforeach()
set(COMPONENT_FOLDERS ${VALID_COMPONENT_FOLDERS})

# Option to build all folders (default ON)
option(BUILD_COMPONENTS_ALL "Build all component folders" ON)

# Option to specify a list of folders to build (semicolon-separated)
# Example: -DCOMPONENTS_FOLDERS="core;textures;tilemap"
set(COMPONENTS_FOLDERS "" CACHE STRING "List of component folders to build (semicolon-separated). Empty means use BUILD_COMPONENTS_ALL or individual flags.")

# Individual folder options (auto-generated)
set(ENABLED_COMPONENT_FOLDERS "")
foreach(FOLDER ${COMPONENT_FOLDERS})
    string(TOUPPER ${FOLDER} FOLDER_UPPER)
    option(BUILD_COMPONENTS_${FOLDER_UPPER} "Build ${FOLDER} components" ON)
    if(BUILD_COMPONENTS_${FOLDER_UPPER})
        list(APPEND ENABLED_COMPONENT_FOLDERS ${FOLDER})
    endif()
endforeach()

# Process folder selection logic
if(COMPONENTS_FOLDERS)
    # Explicit list provided - validate and use it
    set(VALIDATED_FOLDERS "")
    foreach(FOLDER ${COMPONENTS_FOLDERS})
        if(FOLDER IN_LIST COMPONENT_FOLDERS)
            list(APPEND VALIDATED_FOLDERS ${FOLDER})
        else()
            message(WARNING "Component folder '${FOLDER}' does not exist. Available folders: ${COMPONENT_FOLDERS}")
        endif()
    endforeach()
    set(ENABLED_COMPONENT_FOLDERS ${VALIDATED_FOLDERS})
    message(STATUS "Building specified component folders: ${ENABLED_COMPONENT_FOLDERS}")
elseif(BUILD_COMPONENTS_ALL)
    # Build all folders
    set(ENABLED_COMPONENT_FOLDERS ${COMPONENT_FOLDERS})
    message(STATUS "Building all component folders: ${ENABLED_COMPONENT_FOLDERS}")
else()
    # Use individual flags
    message(STATUS "Building component folders based on individual flags: ${ENABLED_COMPONENT_FOLDERS}")
endif()

# Validate that at least one folder is enabled
if(NOT ENABLED_COMPONENT_FOLDERS)
    message(WARNING "No component folders enabled! Please enable at least one folder or set BUILD_COMPONENTS_ALL=ON")
    message(STATUS "Available folders: ${COMPONENT_FOLDERS}")
endif()

# Summary
message(STATUS "=== Component Folder Selection Summary ===")
message(STATUS "Available folders: ${COMPONENT_FOLDERS}")
message(STATUS "Enabled folders: ${ENABLED_COMPONENT_FOLDERS}")
message(STATUS "===========================================")

# Fetch gramarye-libcore
include(FetchContent)
FetchContent_Declare(
    gramarye_libcore
    GIT_REPOSITORY "https://github.com/noahspoling/gramarye-libcore.git"
    GIT_TAG "main"
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
)

# Check if target already exists (from parent using local modules)
if(NOT TARGET gramarye-libcore)
    if(USE_LOCAL_MODULES AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../gramarye-libcore/CMakeLists.txt")
        message(STATUS "gramarye-components: Using local gramarye-libcore")
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../gramarye-libcore gramarye-libcore)
    else()
        FetchContent_MakeAvailable(gramarye_libcore)
    endif()
endif()

# Collect source files from enabled folders
set(ALL_COMPONENT_SRC_FILES "")
if(ENABLED_COMPONENT_FOLDERS)
    message(STATUS "Collecting source files from enabled folders...")
    foreach(FOLDER ${ENABLED_COMPONENT_FOLDERS})
        file(GLOB FOLDER_SRC_FILES "src/${FOLDER}/*.c")
        if(FOLDER_SRC_FILES)
            list(APPEND ALL_COMPONENT_SRC_FILES ${FOLDER_SRC_FILES})
            message(STATUS "  [${FOLDER}] ${FOLDER_SRC_FILES}")
        else()
            message(STATUS "  [${FOLDER}] (no source files found)")
        endif()
    endforeach()
    message(STATUS "Total component source files: ${ALL_COMPONENT_SRC_FILES}")
else()
    message(WARNING "No component folders enabled - library will be empty!")
endif()

# Create library
add_library(gramarye-components 
    ${ALL_COMPONENT_SRC_FILES}
)

# Add include directory
target_include_directories(gramarye-components PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Link against gramarye-libcore
target_link_libraries(gramarye-components PUBLIC gramarye-libcore)

# Export for CMake
include(GNUInstallDirs)
install(TARGETS gramarye-components
    EXPORT componentsTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT componentsTargets
    FILE componentsTargets.cmake
    NAMESPACE gramarye-components::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/components
)

# For FetchContent compatibility
if(NOT TARGET gramarye-components::gramarye-components)
    add_library(gramarye-components::gramarye-components ALIAS gramarye-components)
endif()

