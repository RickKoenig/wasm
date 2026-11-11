//#include <numbers> // C++20 for std::numbers::pi

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double deg2rad(double deg) {
    return deg * M_PI / 180.0;
}
