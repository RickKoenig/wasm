#include <stdio.h>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* texture = NULL;
void* pixels = NULL;
int pitch = 0;

int counter = 0;


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    printf("app init\n");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, "60");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    if (!SDL_CreateWindowAndRenderer("Simple SDL3 Game Loop 2", 256, 256, 0, &window, &renderer)) {
        SDL_Log("Window/Renderer creation failed: %s", SDL_GetError());
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderVSync(renderer, 1);


    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        128,
        128
    );

    SDL_AppResult ar = SDL_APP_CONTINUE;
    return ar;
}

SDL_AppResult SDL_AppIterate(void *appstate) {

    // Get the surface's pixel format details
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_FRect rect = {
        .x = 100.0f,  // Top-left X coordinate
        .y = 150.0f,  // Top-left Y coordinate
        .w = 100.0f,  // Width
        .h = 50.0f   // Height
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &rect);

    if (SDL_LockTexture(texture, NULL, &pixels, &pitch)) {
        Uint32* target_pixels = (Uint32*)pixels;

        // 3. Draw a simple pattern (e.g., fill with a color or gradient)
        for (int y = 0; y < 128; y++) {
            Uint32* row = (Uint32*)((Uint8*)pixels + y * pitch);
            for (int x = 0; x < 128; x++) {
                // RGBA8888 format: red, green, blue, alpha, TODO: check
                row[x] = SDL_MapRGBA(SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888), NULL, x, y, 128, 255);
            }
        }

        // 4. Unlock the texture to apply pixel updates
        SDL_UnlockTexture(texture);
        SDL_RenderTexture(renderer, texture, NULL, NULL);    
    }
    SDL_RenderPresent(renderer);

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
