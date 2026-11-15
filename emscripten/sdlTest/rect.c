#include <SDL3/SDL.h>

void rect(Uint32* pixels, int pitch, int x, int y, int sx, int sy, Uint32 color) {
  // center
  x -= sx / 2;
  y -= sy / 2;
  for (int oy = y; oy < y + sy; ++oy) {
    Uint32* row = (Uint32*)((Uint8*)pixels + oy * pitch);
    for (int ox = x; ox < x + sx; ++ox) {
        row[ox] = color;
    }
  }
}
