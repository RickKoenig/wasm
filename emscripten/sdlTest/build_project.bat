cls

cmake --build build-win
copy build-win\sdlTest.exe .

cmake --build build-web
copy build-web\sdlTest.js .
copy build-web\sdlTest.html .
copy build-web\sdlTest.wasm .
