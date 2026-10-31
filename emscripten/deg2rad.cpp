#include <numbers> // C++20 for std::numbers::pi

double deg2rad(double deg) {
    return deg * std::numbers::pi / 180.0;
}
