cmake_minimum_required(VERSION 3.20)
project(sdlTest LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(EMSCRIPTEN)
    # Generate an .html wrapper alongside .js and .wasm

    # add_executable(sdlTest sdlTest.cpp deg2rad.cpp rect.c)
    add_subdirectory(/nodejs/webasm/emscripten/multi /nodejs/webasm/emscripten/multi/build-web)

    file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp" "*.c")
    add_executable(sdlTest ${SOURCES})
    target_link_libraries(sdlTest PRIVATE /nodejs/webasm/emscripten/multi/build-web/libmulti.a)

    set_target_properties(sdlTest PROPERTIES SUFFIX ".html")

    # Pass Emscripten-specific flags
    target_compile_options(sdlTest PRIVATE -O2)
    target_link_options(sdlTest PRIVATE
        "-lidbfs.js" "-sFORCE_FILESYSTEM=1"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sUSE_SDL=3"
        # Optional: bundle assets into the virtual filesystem
        "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/fileData@fileData"
        "SHELL:--shell-file ${CMAKE_SOURCE_DIR}/custom_shell.html"
    )

    # Gather all files in the assets folder
    file(GLOB_RECURSE ASSET_FILES "${CMAKE_SOURCE_DIR}/fileData/*")

    # Force CMake to re-run the linker if any asset file changes
    set_target_properties(sdlTest PROPERTIES LINK_DEPENDS "${ASSET_FILES}")
    set_target_properties(sdlTest PROPERTIES LINK_DEPENDS "${ASSET_FILES};${CMAKE_SOURCE_DIR}/custom_shell.html")

elseif(WIN32)
    # Native Windows libraries and settings

    # add_executable(sdlTest sdlTest.cpp deg2rad.cpp rect.c)
    add_subdirectory(/nodejs/webasm/emscripten/multi /nodejs/webasm/emscripten/multi/build-win)

    file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp" "*.c")
    add_executable(sdlTest ${SOURCES})

    target_link_libraries(sdlTest PRIVATE /nodejs/webasm/emscripten/multi/build-win/multi.lib)

    target_compile_definitions(sdlTest PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
    # Example: link native dependencies
    # find_package(SDL3 REQUIRED)
    target_include_directories(sdlTest PRIVATE C:/SDL3/include)
    target_link_libraries(sdlTest PRIVATE C:/sdl3/lib/x86/sdl3.lib)
endif()
    
target_include_directories(sdlTest PRIVATE ../multi)






#[[

# 1. Define the external library as an IMPORTED target
add_library(external_lib UNKNOWN IMPORTED)

# 2. Point it to the actual file path on disk
set_target_properties(external_lib PROPERTIES
    IMPORTED_LOCATION "/path/to/libexternal.a"
)

# 3. Link it to your executable
add_executable(main_app main.cpp)
target_link_libraries(main_app PRIVATE external_lib)

]]