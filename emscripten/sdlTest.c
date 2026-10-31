// Copyright 2011 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#include <stdio.h>
#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

//#define ANIMATE

static int deg;
static int scan;
static SDL_Surface *screen;

double deg2rad(double deg) {
    return deg * M_PI / 180.0;
}

void rect(int x, int y, int sx, int sy, int r, int g, int b, int a) {
  // center
  x -= sx / 2;
  y -= sy / 2;
  for (int oy = y; oy < y + sy; ++oy) {
    for (int ox = x; ox < x + sx; ++ox) {
      *((Uint32*)screen->pixels + oy * 256 + ox) = SDL_MapRGBA(screen->format, r, g, b, a);//j, 255-i, alpha);  
    }
  }
}

bool one_iter(double time, void* userData) {
  //printf("in one iter deg = %d\n", deg);
  if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
  float rad = deg2rad(deg);
  int rx = 96 * cos(rad);
  int ry = 96 * sin(rad);
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < 256; i++) {
#ifdef TEST_SDL_LOCK_OPTS
      // Alpha behaves like in the browser, so write proper opaque pixels.
      int alpha = 255;
#else
      // To emulate native behavior with blitting to screen, alpha component is ignored. Test that it is so by outputting
      // data (and testing that it does get discarded)
      int alpha = (i+j) % 255;
#endif
      *((Uint32*)screen->pixels + j * 256 + i) = SDL_MapRGBA(screen->format, i, j, 0, 0);//j, 255-i, alpha);
    }
  }
  rect(128 + rx, 128 + ry,   20, 20,   0, 0, 255, 255); // circle
  rect(128 + rx, 10,   20, 20,   255, 0, 0, 255); // horz 
  rect(10, 128 + ry,   20, 20,   0, 255, 0, 255); // vert
  rect(scan, 64,   20, 20,   255, 255, 255, 255); // fps scan
  if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  SDL_Flip(screen);
  ++deg;
  if (deg >= 360) {
    deg -= 360;
  }
  
  ++scan;
  if (scan >= 256) {
    scan -= 256;
  }
  return true;
}

int main(int argc, char** argv) {
  printf("Hello, world!\n");

  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(256, 256, 32, SDL_SWSURFACE);

#ifdef TEST_SDL_LOCK_OPTS
  EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif

#ifdef ANIMATE
  emscripten_request_animation_frame_loop(&one_iter, 0);
#else
  one_iter(0, NULL);
#endif


  printf("you should see a smoothly-colored square - no sharp lines but the square borders!\n");
  printf("and here is some text that should be HTML-friendly: amp: |&| double-quote: |\"| quote: |'| less-than, greater-than, html-like tags: |<cheez></cheez>|\nanother line.\n");

  SDL_Quit();

  return 0;
}