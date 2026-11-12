cls
rem "REM build a wasm for the dist2 function
@rem emcc --target=wasm32-unknown-emscripten -nostdlib -Wl,--no-entry -Wl,--export-all dist2.c -o dist2.wasm
clang --target=wasm32-wasip1 -nostdlib -Wl,--no-entry -Wl,--export-all -DWASM dist2.c -o dist2.wasm
rem "REM build a .exe with the dist2 function"
clang dist2test.c dist2.c -o dist2test.exe
