cls

@rem C++
@rem scratch
clang scratch.cpp ../numath/deg2rad.cpp -I../numath/ -m32 -std=c++20 -o scratch.exe
em++ scratch.cpp ../numath/deg2rad.cpp -I../numath/ -std=c++20 --preload-file ../fileData -o scratch.html
