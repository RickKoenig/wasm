cls
rem Compile the project using the generated build artifacts
cmake --build build
rem cmake --build buildWasm
clang --target=wasm32-wasip1 -DWASM -nostdlib -Wl,--no-entry -Wl,--export-all dist2.c -o dist2.wasm

copy build\debug\dist2test.exe .
rem copy buildWasm\dist2test.wasm .
rem copy buildWasm\dist2test.js .
