cmake_minimum_required(VERSION 3.20)
project(sdlTest LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(EMSCRIPTEN)
    # Generate an .html wrapper alongside .js and .wasm
    add_subdirectory(../multi ${CMAKE_BINARY_DIR}/multi)
    add_executable(sdlTest 
        sdlTest.cpp
        rect.c
        fileSystemInit.cpp
        deg2rad.cpp
    )
    target_link_libraries(sdlTest PRIVATE multi)
    set_target_properties(sdlTest PROPERTIES SUFFIX ".html")
    # Pass Emscripten-specific flags
    target_compile_options(sdlTest PRIVATE -O2)
    target_link_options(sdlTest PRIVATE
        "-lidbfs.js" "-sFORCE_FILESYSTEM=1"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sUSE_SDL=3"
        "-O2"
        # Optional: bundle assets into the virtual filesystem
        "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/fileData@fileData"
        "SHELL:--shell-file ${CMAKE_SOURCE_DIR}/custom_shell.html"
    )
    # Gather all files in the assets folder
    file(GLOB_RECURSE ASSET_FILES "${CMAKE_SOURCE_DIR}/fileData/*")
    # Force CMake to re-run the linker if any asset file changes
    set_target_properties(sdlTest PROPERTIES LINK_DEPENDS "${ASSET_FILES};${CMAKE_SOURCE_DIR}/custom_shell.html")
    target_include_directories(sdlTest PRIVATE ../multi)

elseif(WIN32)
    # Native Windows libraries and settings
    add_subdirectory(../multi ${CMAKE_BINARY_DIR}/multi)
    add_executable(sdlTest
        sdlTest.cpp
        rect.c
        fileSystemInit.cpp
        deg2rad.cpp
    )
    # Hide console window in Release mode only
    
    set_target_properties(sdlTest PROPERTIES
        WIN32_EXECUTABLE "$<CONFIG:Release>"
    )
    
    target_compile_definitions(sdlTest PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
    target_include_directories(sdlTest PRIVATE C:/SDL3/include)
    target_include_directories(sdlTest PRIVATE ../multi)
    target_link_libraries(sdlTest PRIVATE C:/sdl3/lib/x86/sdl3.lib)
    target_link_libraries(sdlTest PRIVATE multi)
endif()
