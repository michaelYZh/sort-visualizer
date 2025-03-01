cmake_minimum_required(VERSION 3.15)
project(GraphicalSorting VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compile options
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Set the path to the Conan-generated CMake files
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# Find dependencies using Conan
find_package(SFML REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/visualization.cpp
    src/ui.cpp
    src/sorting_algorithms.cpp
)

# Header files
set(HEADERS
    include/visualization.h
    include/ui.h
    include/sorting_algorithms.h
)

# Create executable
add_executable(GraphicalSorting ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(GraphicalSorting PRIVATE include)

# Link libraries
target_link_libraries(GraphicalSorting PRIVATE 
    sfml::sfml
)

# Create assets directory if it doesn't exist
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/asset)

# Copy assets to build directory
add_custom_command(TARGET GraphicalSorting POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/asset $<TARGET_FILE_DIR:GraphicalSorting>/asset
)

# Install
install(TARGETS GraphicalSorting
    RUNTIME DESTINATION bin
)
install(DIRECTORY asset/
    DESTINATION bin/asset
) 