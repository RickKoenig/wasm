#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cmath>
//#include <numbers> // C++20 for std::numbers::pi
#include "deg2rad.h"

/*
double deg2rad(double deg) {
    return deg * std::numbers::pi / 180.0;
}
*/

void readFile(const char* fname) {
    // add path to fileData
    std::string newFname = "../fileData/";
    newFname += fname;
    FILE *file = fopen(newFname.c_str(), "rb");
    printf("filename = '%s'\n", fname);
    if (!file) {
        printf("cannot open file\n");
    }
    while (!feof(file)) {
        char c = fgetc(file);
        if (c != EOF) {
        putchar(c);
        }
    }
    fclose(file);
}

int main() {
    std::cout << "Hello, World! scratch C++\n";
    double* const table = new double[91];
    for (double deg = 0.0; deg <= 90.0; ++deg) {
        const double s = sin(deg2rad(deg));
        table[static_cast<int>(deg)] = s;
    }
    for (int deg = 0; deg <= 90; ++deg) {
        const double s = table[deg];
        std::cout << "deg = " << deg << ", sin = " << s << std::endl;
    }
    delete[] table;
    readFile("hello_world_file2.txt");
    readFile("hello_world_file.txt");
    return 0;
}