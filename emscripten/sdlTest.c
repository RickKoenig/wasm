#include <stdio.h>
#include <time.h>

#ifdef __EMSCRIPTEN__
#include <SDL/SDL.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#else
#include <SDL3/SDL.h>
#endif

//#define ANIMATE
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// object state
static int deg;
static int scan;

// surface and misc
static SDL_Surface *surface;
#ifndef __EMSCRIPTEN__  // NATIVE
SDL_Window* window;
long busySecs = 5; // how long to busy wait on this window, showing graphics, then exit // MINIMAL

void busySleep(long ms) {
    clock_t start = clock();
    clock_t end = clock() + ms * 1000 / CLOCKS_PER_SEC;
    while(true) {
      start = clock();
      if (start >= end)
        break;
    }
}
#endif

double deg2rad(double deg) {
    return deg * M_PI / 180.0;
}

void rect(int x, int y, int sx, int sy, Uint32 color) {
  // center
  x -= sx / 2;
  y -= sy / 2;
  for (int oy = y; oy < y + sy; ++oy) {
    for (int ox = x; ox < x + sx; ++ox) {
      *((Uint32*)surface->pixels + oy * 256 + ox) = color;
    }
  }
}

// unified mapRGB between SDL versions 1 and 3
#ifdef __EMSCRIPTEN__
Uint32 mapRGB(const SDL_PixelFormat* fmtDetails, Uint8 r, Uint8 g, Uint8 b) {
 Uint32 color = SDL_MapRGB(fmtDetails, r, g, b);
 return color;
}
#else
Uint32 mapRGB(const SDL_PixelFormatDetails* fmtDetails, Uint8 r, Uint8 g, Uint8 b) {
  Uint32 color = SDL_MapRGB(fmtDetails, NULL, r, g, b);
  return color;
}
#endif

// draw one frame
bool one_iter(double time, void* userData) {
  //printf("in one iter deg = %d\n", deg);

// clear surface
#ifdef __EMSCRIPTEN__
  const SDL_PixelFormat* fmtDetails = surface->format;
  Uint32 clearColor = SDL_MapRGB(fmtDetails, 255, 255, 0);
  SDL_FillRect(surface, NULL, clearColor);
#else
  // Get the surface's pixel format details
  const SDL_PixelFormatDetails* fmtDetails = SDL_GetPixelFormatDetails(surface->format);
  int clearColor = SDL_MapRGB(fmtDetails, NULL, 255, 255, 0);
  SDL_FillSurfaceRect(surface, NULL, clearColor);
#endif

// lock surface and draw color gradient pixels
  if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
  float rad = deg2rad(deg);
  int rx = 96 * cos(rad);
  int ry = 96 * sin(rad);
  for (int j = 0; j < 128; j++) {
    for (int i = 0; i < 256; i++) {
/*#ifdef __EMSCRIPTEN__
      *((Uint32*)surface->pixels + j * 256 + i) = SDL_MapRGB(fmtDetails, i, j, 0);
#else
      *((Uint32*)surface->pixels + j * 256 + i) = SDL_MapRGB(fmtDetails, NULL, i, j, 0);
#endif*/
      *((Uint32*)surface->pixels + j * 256 + i) = mapRGB(fmtDetails, i, j, 0);
    }
  }

// draw simple objects
  rect(128 + rx, 128 + ry,   20, 20, mapRGB(fmtDetails, 255, 0, 0)); // circle
  rect(128 + rx, 10,   20, 20, mapRGB(fmtDetails, 0, 255, 0)); // horz 
  rect(10, 128 + ry,   20, 20, mapRGB(fmtDetails, 0, 0, 255)); // vert
  rect(scan, 64,   20, 20, mapRGB(fmtDetails, 255, 255, 255)); // fps scan

// unlock and flip surface
  if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
#ifdef __EMSCRIPTEN__
  SDL_Flip(surface);
#else
  SDL_UpdateWindowSurface(window);
#endif

// update objects state
  deg += 6; // 6 * 60 = 360, try for 60 FPS, one revolution per second
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
// intro
#ifdef __EMSCRIPTEN__
  printf("Hello, world! EMSCRIPTEN\n");
#else
  printf("Hello, world! NATIVE\n");
#endif

// version
#ifdef __EMSCRIPTEN__
  SDL_version compiled;
  SDL_VERSION(&compiled);       // Get version compiled against (Macro)
  printf("SDL version compiled = %d.%d\n", compiled.major, compiled.minor);
  //SDL_version linked;
  //SDL_GetVersion(&linked);      // Get current running version (Function)
  //printf("SDL version linked = %d.%d\n", linked.major, linked.minor);
#else
  printf("SDL version compiled = %d.%d\n", SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
#endif

// init video
#ifdef __EMSCRIPTEN__
  SDL_Init(SDL_INIT_VIDEO);
  surface = SDL_SetVideoMode(256, 256, 32, SDL_SWSURFACE);
#else
  bool result = SDL_Init(SDL_INIT_VIDEO);
  printf("SDL result value init video %d\n", result);
  window = SDL_CreateWindow("SDL test 2D", 256, 256, 0);
  surface = SDL_GetWindowSurface(window);
#endif

// draw
#ifdef __EMSCRIPTEN__
#ifdef ANIMATE
  emscripten_request_animation_frame_loop(&one_iter, 0);
#else
  one_iter(0, NULL);
#endif
#else
#ifdef NO //ANIMATE
  emscripten_request_animation_frame_loop(&one_iter, 0);
#else
  one_iter(0, NULL);
#endif
#endif

// exit
#ifndef __EMSCRIPTEN__
  busySleep(busySecs * 1000); // ms/sec
#endif
  printf("you should see a smoothly-colored square - no sharp lines but the square borders!\n");
  printf("and here is some text that should be HTML-friendly: amp: |&| double-quote: |\"| quote: |'| less-than, greater-than, html-like tags: |<cheez></cheez>|\nanother line.\n");
  SDL_Quit();
  return 0;
}


#ifndef __EMSCRIPTEN__


#define SDL_MAIN_USE_CALLBACKS 1  // Tell SDL3 to use the callback system
#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>

// Your custom application state structure
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} AppState;

// 1. Called once when the app starts (Setup)
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_APP_FAILURE;
    }

    AppState *state = SDL_calloc(1, sizeof(AppState));
    if (!state) {
        return SDL_APP_FAILURE;
    }
    *appstate = state;

    if (!SDL_CreateWindowAndRenderer("SDL3 Frame Loop", 640, 480, 0, &state->window, &state->renderer)) {
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE; // Continue running the loop
}

// 2. Called every frame (The Main Loop / RequestAnimationFrame equivalent)
SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState *state = (AppState *)appstate;

    // Render logic goes here
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
    SDL_RenderClear(state->renderer);
    
    // Draw things...

    SDL_RenderPresent(state->renderer);

    return SDL_APP_CONTINUE; // Keep looping. Return SDL_APP_SUCCESS to quit normally.
}

// 3. Called every time an event occurs
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // Signal SDL to quit cleanly
    }
    return SDL_APP_CONTINUE;
}

// 4. Called once when exiting (Cleanup)
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    if (appstate) {
        AppState *state = (AppState *)appstate;
        SDL_DestroyRenderer(state->renderer);
        SDL_DestroyWindow(state->window);
        SDL_free(state);
    }
    SDL_Quit();
}


#endif
