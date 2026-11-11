cls

@rem custom HTML
@rem dist2
clang dist2test.c ../numath/dist2.c -I../numath/ -m32 -o dist2test.exe
emcc ../numath/dist2.c -o dist2.js -s "EXPORTED_FUNCTIONS=[_dist2]" -s "EXPORTED_RUNTIME_METHODS=[ccall, cwrap]"
