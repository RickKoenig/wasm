cmake_minimum_required(VERSION 3.20)
project(sdlTest LANGUAGES C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sdlTest sdlTest.c)

if(EMSCRIPTEN)
    # Generate an .html wrapper alongside .js and .wasm
    set_target_properties(sdlTest PROPERTIES SUFFIX ".html")

    # Pass Emscripten-specific flags
    target_compile_options(sdlTest PRIVATE -O2)
    target_link_options(sdlTest PRIVATE
        "-sALLOW_MEMORY_GROWTH=1"
        "-sUSE_SDL=3"
        # Optional: bundle assets into the virtual filesystem
        # "--preload-file" "${CMAKE_SOURCE_DIR}/assets@/assets"
    )
elseif(WIN32)
    # Native Windows libraries and settings
    target_compile_definitions(sdlTest PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
    # Example: link native dependencies
    # find_package(SDL3 REQUIRED)
    target_include_directories(sdlTest PRIVATE C:/SDL3/include)
    target_link_libraries(sdlTest PRIVATE C:/sdl3/lib/x86/sdl3.lib)
endif()