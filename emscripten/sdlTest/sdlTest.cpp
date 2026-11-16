#include <stdio.h>
#include <math.h>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "deg2rad.h"
#include "rect.h"

#include <timesTwo.h>
#include <timesThree.h>
#include <timesFour.h>

// sdl objects
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
const SDL_PixelFormatDetails* fmtDetails = NULL;
SDL_Texture* texture = NULL;

// user object state
static int deg;
static int scan;
const static int winWidth = 256;
const static int winHeight = 256;
int counter = 0;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    printf("sdlTest2 init\n");
    printf("SDL version compiled = %d.%d.%d\n", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);
    printf("sizeof void* = %zu\n", sizeof (void *));

    float testA = 10;
    float testA2 = timesTwo(testA);
    float testA3 = timesThree(testA);
    float testA4 = timesFour(testA);
    printf("a = %f, a2 = %f, a3 = %f, a4 = %f\n", testA, testA2, testA3, testA4);
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, "60");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    fmtDetails = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
    if (!SDL_CreateWindowAndRenderer("sdltest 2", winWidth, winHeight, 0, &window, &renderer)) {
        SDL_Log("Window/Renderer creation failed: %s", SDL_GetError());
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderVSync(renderer, 1);

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        winWidth,
        winHeight
    );

    SDL_AppResult ar = SDL_APP_CONTINUE;
    return ar;
}

// draw one frame
SDL_AppResult SDL_AppIterate(void *appstate) {
    // clear surface
    //SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    //SDL_RenderClear(renderer);

    // lock surface and draw color gradient pixels
    Uint32* pixels = NULL;
    int pitch = 0;
    if (SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch)) {
        // draw a color gradient
        Uint32* target_pixels = pixels;
        for (int y = 0; y < winHeight; y++) {
            Uint32* row = (Uint32*)((Uint8*)pixels + y * pitch);
            for (int x = 0; x < winWidth; x++) {
                // RGBA8888 format: red, green, blue, alpha, TODO: check
                row[x] = SDL_MapRGB(fmtDetails, NULL, x, y, 0);
            }
        }

        // draw simple objects with cpu on locked surface
        float rad = deg2rad(deg);
        int rx = 3 * winWidth * cos(rad) / 8;
        int ry = 3 * winHeight * sin(rad) / 8;
        rect(pixels, pitch, winWidth / 2 + rx, winWidth / 2 + ry,   20, 20, SDL_MapRGB(fmtDetails, NULL, 255, 0, 0)); // circle
        rect(pixels, pitch, winWidth / 2 + rx, 10,   20, 20, SDL_MapRGB(fmtDetails, NULL, 0, 255, 0)); // horz 
        rect(pixels, pitch, 10, winHeight / 2 + ry,   20, 20, SDL_MapRGB(fmtDetails, NULL, 0, 0, 255)); // vert
        rect(pixels, pitch, scan, 64,   20, 20, SDL_MapRGB(fmtDetails, NULL, 255, 255, 255)); // fps scan

        SDL_UnlockTexture(texture);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
    }  

    SDL_FRect rect = {
        .x = 10,  // Top-left X coordinate
        .y = 10,  // Top-left Y coordinate
        .w = 40,  // Width
        .h = 20   // Height
    };

    SDL_SetRenderDrawColor(renderer, 255, 180, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    // update objects state
    deg += 6; // 6 * 60 = 360, try for 60 FPS, one revolution per second
    if (deg >= 360) {
        deg -= 360;
    }
    scan += 4;
    if (scan >= winWidth) {
        scan -= winWidth;
    }
    if (!(counter % 60)) printf("count = %d\n", counter / 60);
    ++counter;
    SDL_AppResult ar = SDL_APP_CONTINUE;
    return ar;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    } else if (event->type == SDL_EVENT_KEY_DOWN) {
        if (event->key.key == SDLK_ESCAPE) {
            return SDL_APP_SUCCESS;
        }
        if (event->key.key == 'q') { // quit
            return SDL_APP_SUCCESS;
        }
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
