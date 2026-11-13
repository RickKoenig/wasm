# 1. Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.23)

# 2. Define the project name and language
project(MyProject LANGUAGES C)

# 3. Set the C++ standard (optional, recommended)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Define the executable target and its source files
add_executable(dist2test dist2test.c dist2.c)

message(STATUS "This is a clean notice.")

if(WIN32)
    message(STATUS "This is WIN32 path")
else()
    message(STATUS "This is not WIN32 path")
endif()


message(STATUS "C Compiler: ${CMAKE_C_COMPILER} (${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION})")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER} (${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION})")



# Create a target that always runs during a build
#add_custom_target(copy_final_files ALL
    #COMMAND ${CMAKE_COMMAND} -E copy_if_different
    #    "${CMAKE_CURRENT_SOURCE_DIR}/config.json"
    #    "$<TARGET_FILE_DIR:my_target>/config.json"
    #COMMENT "Copying built files and assets to deploy directory"
#)

# Force this target to wait until my_app and my_lib finish building
#add_dependencies(copy_final_files dist2test)
