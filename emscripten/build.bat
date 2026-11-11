cls

@rem @goto skip1
@rem simple cases
@rem simple
clang simple.c -m32 -o simple.exe
emcc simple.c -o simple.html

@rem custom HTML
@rem dist2
clang dist2test.c dist2.c -m32 -o dist2test.exe
emcc dist2.c -o dist2.js -s "EXPORTED_FUNCTIONS=[_dist2]" -s "EXPORTED_RUNTIME_METHODS=[ccall, cwrap]"

:skip1
@rem C++
@rem scratch
clang scratch.cpp deg2rad.cpp -m32 -std=c++20 -o scratch.exe
em++ scratch.cpp deg2rad.cpp -std=c++20 --preload-file fileData -o scratch.html
goto skip2

@rem sdl3
@rem sdltest
clang sdlTest.c -m32 -IC:\SDL3\include -LC:\sdl3\lib\x86 -lSDL3.lib -Xlinker /SUBSYSTEM:CONSOLE -o sdlTest.exe
emcc sdlTest.c -sUSE_SDL=3 -o sdlTest.html
:skip2

