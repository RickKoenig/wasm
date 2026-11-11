#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// test malloc, free and trig math
int main() {
#ifdef __EMSCRIPTEN__
  printf("SIMPLE from emscripten\n");
#else
  printf("SIMPLE from NATIVE\n");
#endif
  float* table = malloc(91 * sizeof(float));
  printf("sizeof void* = %zu\n", sizeof(void*));
  for (int i = 0; i <= 90; ++i) {
      const float rad = (float)i * M_PI / 180;
      const float s = sin(rad);
      table[i] = s;
  }
  for (int i = 0; i <= 90; i += 5) {
      const float s = table[i];
      printf("deg = %d, sine = %f\n", i, s);
  }
  free(table);
  printf("done!\n");
  return 0;
}
