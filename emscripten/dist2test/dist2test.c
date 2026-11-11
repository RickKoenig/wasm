#include <stdio.h>
#include <stdlib.h>
#include "dist2.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
#ifdef __EMSCRIPTEN__
    printf("dist2test from emscripten\n");
#else
    printf("dist2test from NATIVE\n");
#endif
    for (float f = 0; f <= 90.0f; f += .5f) {
        const float rad = f * M_PI / 180;
        const float s = sin(rad);
        printf("f = %6.3f, rad = %f, sine = %f\n", f, rad, s);
    }
    
    printf("malloc\n");
    int* ptr = malloc(1000000UL);
    free(ptr);
    ptr = NULL;
    printf("free\n");
    
	float a = 3;
	float b = 4;
	float d2 = dist2(a, b);
	printf("dist2 = %f\n",d2);
	return 0;
}
