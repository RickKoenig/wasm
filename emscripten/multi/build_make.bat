cls
cmake -B build-win -DCMAKE_C_FLAGS="-m32" -DCMAKE_CXX_FLAGS="-m32" -G Ninja
emcmake cmake -B build-web -DCMAKE_C_FLAGS="-m32" -DCMAKE_CXX_FLAGS="-m32" -G Ninja
