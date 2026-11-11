cls

@rem sdl3
@rem sdltest
clang sdlTest.c -m32 -IC:\SDL3\include -I../numath -LC:\sdl3\lib\x86 -lSDL3.lib -Xlinker /SUBSYSTEM:CONSOLE -o sdlTest.exe
emcc sdlTest.c -sUSE_SDL=3 -o sdlTest.html
