// Copyright 2011 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.
#include <stdio.h>
#include <time.h>

#ifdef __EMSCRIPTEN__
#include <SDL/SDL.h>
#else
#include <SDL3/SDL.h>
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

//#define ANIMATE
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void busySleep(long ms) {
    clock_t start = clock();
    clock_t end = clock() + ms * 1000 / CLOCKS_PER_SEC;
    while(true) {
      start = clock();
      if (start >= end)
        break;
    }
}

static int deg;
static int scan;

static SDL_Surface *surface;

#ifndef __EMSCRIPTEN__
SDL_Window* window;
#endif

double deg2rad(double deg) {
    return deg * M_PI / 180.0;
}

void rect(int x, int y, int sx, int sy, int r, int g, int b, int a) {
  // center
  x -= sx / 2;
  y -= sy / 2;
  for (int oy = y; oy < y + sy; ++oy) {
    for (int ox = x; ox < x + sx; ++ox) {
      //*((Uint32*)surface->pixels + oy * 256 + ox) = SDL_MapRGBA(surface->format, r, g, b, a);//j, 255-i, alpha);  
    }
  }
}
#ifdef __EMSCRIPTEN__
bool one_iter(double time, void* userData) {
  //printf("in one iter deg = %d\n", deg);
  if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
  float rad = deg2rad(deg);
  int rx = 96 * cos(rad);
  int ry = 96 * sin(rad);
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < 256; i++) {
#ifdef TEST_SDL_LOCK_OPTS
      // Alpha behaves like in the browser, so write proper opaque pixels.
      int alpha = 255;
#else
      // To emulate native behavior with blitting to surface, alpha component is ignored. Test that it is so by outputting
      // data (and testing that it does get discarded)
      int alpha = (i+j) % 255;
#endif
      *((Uint32*)surface->pixels + j * 256 + i) = SDL_MapRGBA(surface->format, i, j, 0, 0);//j, 255-i, alpha);
    }
  }
  rect(128 + rx, 128 + ry,   20, 20,   0, 0, 255, 255); // circle
  rect(128 + rx, 10,   20, 20,   255, 0, 0, 255); // horz 
  rect(10, 128 + ry,   20, 20,   0, 255, 0, 255); // vert
  rect(scan, 64,   20, 20,   255, 255, 255, 255); // fps scan
  if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
  SDL_Flip(surface);
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

  SDL_version compiled;
  SDL_version linked;

  SDL_VERSION(&compiled);       // Get version compiled against (Macro)
  //SDL_GetVersion(&linked);      // Get current running version (Function)
  printf("SDL version compiled = %d.%d\n", compiled.major, compiled.minor);
  //printf("SDL version linked = %d.%d\n", linked.major, linked.minor);


  SDL_Init(SDL_INIT_VIDEO);
  surface = SDL_SetVideoMode(256, 256, 32, SDL_SWSURFACE);

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

#else // NATIVE

bool one_iter(double time, void* userData) {
  printf("in one iter deg = %d\n", deg);
  if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
  
  float rad = deg2rad(deg);
  int rx = 96 * cos(rad);
  int ry = 96 * sin(rad);
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < 256; i++) {
#ifdef TEST_SDL_LOCK_OPTS
      // Alpha behaves like in the browser, so write proper opaque pixels.
      int alpha = 255;
#else
      // To emulate native behavior with blitting to surface, alpha component is ignored. Test that it is so by outputting
      // data (and testing that it does get discarded)
      int alpha = (i+j) % 255;
#endif
      const SDL_PixelFormatDetails* fmtDetails = SDL_GetPixelFormatDetails(surface->format);
      *((Uint32*)surface->pixels + j * 256 + i) = SDL_MapRGB(fmtDetails, NULL, i, j, 0);//j, 255-i, alpha);
    }
  }
  
  rect(128 + rx, 128 + ry,   20, 20,   0, 0, 255, 255); // circle
  rect(128 + rx, 10,   20, 20,   255, 0, 0, 255); // horz 
  rect(10, 128 + ry,   20, 20,   0, 255, 0, 255); // vert
  rect(scan, 64,   20, 20,   255, 255, 255, 255); // fps scan
  if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
  //SDL_Flip(surface);
  ++deg;
  if (deg >= 360) {
    deg -= 360;
  }
  
  ++scan;
  if (scan >= 256) {
    scan -= 256;
  }
  SDL_UpdateWindowSurface(window);
  return true;
}

int main(int argc, char** argv) {
  printf("Hello, world! NATIVE\n");
  printf("SDL version compiled = %d.%d\n", SDL_MAJOR_VERSION, SDL_MINOR_VERSION);

  bool result = false;
  result = SDL_Init(SDL_INIT_VIDEO);
  printf("SDL result value init video %d\n", result);
  // surface = SDL_SetVideoMode(256, 256, 32, SDL_SWSURFACE);
  window = SDL_CreateWindow("My Game", 256, 256, 0);
  surface = SDL_GetWindowSurface(window);
  //int color = 255;
// Get the surface's pixel format details
const SDL_PixelFormatDetails* fmtDetails = SDL_GetPixelFormatDetails(surface->format);
  int color = SDL_MapRGB(fmtDetails, NULL, 255, 255, 0);
  SDL_FillSurfaceRect(surface, NULL, color);
  // 3. Update the window to make the surface changes visible
/*

#ifdef TEST_SDL_LOCK_OPTS
  EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif
*/
#ifdef ANIMATE
  emscripten_request_animation_frame_loop(&one_iter, 0);
#else
  one_iter(0, NULL);
#endif


  printf("you should see a smoothly-colored square - no sharp lines but the square borders!\n");
  printf("and here is some text that should be HTML-friendly: amp: |&| double-quote: |\"| quote: |'| less-than, greater-than, html-like tags: |<cheez></cheez>|\nanother line.\n");


  busySleep(3000);
  printf("calling SDL_Quit\n");
  SDL_Quit();
  return 0;
}
#endif
