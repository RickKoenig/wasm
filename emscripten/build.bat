cls

goto skip1
rem scratch
clang scratch.cpp deg2rad.cpp -std=c++20 -o scratch.exe
em++ scratch.cpp deg2rad.cpp -std=c++20 -o scratch.html

:skip1
rem sdltest
clang sdlTest.c -IC:\SDL3\include -LC:\sdl3\lib\x64 -lSDL3.lib -o sdlTest.exe
rem emcc sdlTest.c --use-port=sdl3 -o sdlTest.html
rem emcc sdlTest.c -sUSE_SDL=3 -o sdlTest.html
emcc sdlTest.c -o sdlTest.html

rem sdlGameLoop
clang sdlGameLoop.c -IC:\SDL3\include -LC:\sdl3\lib\x64 -lSDL3.lib -Xlinker /SUBSYSTEM:WINDOWS -o sdlGameLoop.exe
emcc sdlGameLoop.c -sUSE_SDL=3 -o sdlGameLoop.html
rem clang sdlGameLoop2.c -o sdlGameLoop2.exe
rem clang sdlGameLoop2.c -IC:\SDL3\include -LC:\sdl3\lib\x64 -lSDL3.lib -o sdlGameLoop2.exe
rem clang sdlGameLoop2.c -IC:\SDL3\include -LC:\sdl3\lib\x64 -lSDL3.lib -Xlinker /SUBSYSTEM:WINDOWS -o sdlGameLoop2.exe
clang sdlGameLoop2.c -IC:\SDL3\include -LC:\sdl3\lib\x64 -lSDL3.lib -Xlinker /SUBSYSTEM:CONSOLE -o sdlGameLoop2.exe
emcc sdlGameLoop2.c -sUSE_SDL=3 -o sdlGameLoop2.html
goto skip2

rem files
clang files.cpp -o files.exe
rem em++ files.cpp -o files.html --preload-file fileData/hello_world_file.txt

rem hello
clang hello.c -o hello.exe
emcc hello.c -o hello.html

rem hello2
clang hello2.c -o hello2.exe
emcc hello2.c -sALLOW_MEMORY_GROWTH -o hello2.js

rem simple
clang simple.c -o simple.exe
emcc simple.c -sALLOW_MEMORY_GROWTH -o simple.html

rem dist2
clang dist2test.c dist2.c -o dist2test.exe
emcc dist2.c -o dist2.js -s "EXPORTED_FUNCTIONS=[_dist2]" -s "EXPORTED_RUNTIME_METHODS=[ccall, cwrap]"

:skip2