cls

cmake --build build-win/debug
cmake --build build-win/release
copy build-win\debug\sdlTest.exe sdlTest_d.exe
copy build-win\release\sdlTest.exe .

cmake --build build-web
copy build-web\sdlTest.js .
copy build-web\sdlTest.html .
copy build-web\sdlTest.wasm .
copy build-web\sdlTest.data .
