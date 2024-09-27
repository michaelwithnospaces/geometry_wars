# Specify the minimum required version of CMake for this project
cmake_minimum_required(VERSION 3.2)

# Define the project name and specify it is a C++ project
project(ASSIGNMENT_1 CXX)

# Set the C++ standard to C++11 and make it a required standard (C++11 or higher)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add a preprocessor definition to the project, which defines PLAT_RAYLIB.
# This is equivalent to adding `#define PLAT_RAYLIB` in the source code,
# useful for platform-specific compilation flags or conditional compilation.
add_compile_definitions(PLAT_RAYLIB)

# Use the 'file' command to recursively find all .cpp files in the src/ directory
# and store them in the PROJECT_SOURCES variable. 
# The CONFIGURE_DEPENDS flag ensures that the list is regenerated if files are added/removed.
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

# Add an executable to the project using the defined project name and source files.
# This creates the actual binary for the project.
add_executable(${PROJECT_NAME})

# Link the collected source files (PROJECT_SOURCES) to the executable.
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})

# Set the include directories (for header files) that are private to this target.
# In this case, PROJECT_INCLUDE should be a path to the include directory with headers for this project.
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

# Link the Raylib library to the project. This ensures the Raylib functions and symbols 
# are available to your project during linking.
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)