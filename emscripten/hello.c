#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
#ifdef __EMSCRIPTEN__
    printf("h e l l o from emscripten\n");
#else
    printf("h e l l o from NATIVE\n");
#endif

    for (float f = 0; f <= 90.0f; f += 5) {
        const float rad = f * M_PI / 180;
        const float s = sin(rad);
        printf("f = %6.3f, rad = %f, sine = %f\n", f, rad, s);
    }
    return 0;
}
