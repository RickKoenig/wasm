cls

cmake -B build-win/debug -DCMAKE_C_FLAGS="-m32" -DCMAKE_CXX_FLAGS="-m32" -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake -B build-win/release -DCMAKE_C_FLAGS="-m32" -DCMAKE_CXX_FLAGS="-m32" -G Ninja -DCMAKE_BUILD_TYPE=Release

emcmake cmake -B build-web -DCMAKE_C_FLAGS="-m32" -DCMAKE_CXX_FLAGS="-m32" -G Ninja
