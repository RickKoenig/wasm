#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {
    // 1. Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }

    // 2. Create Window and Renderer
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if (!SDL_CreateWindowAndRenderer("Simple SDL3 Game Loop", 800, 600, 0, &window, &renderer)) {
        SDL_Log("Window/Renderer creation failed: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    bool is_running = true;
    SDL_Event event;

    // 3. Main Game Loop
    while (is_running) {
        // Event Polling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_ESCAPE) {
                    is_running = false;
                }
            }
        }

        // Update Game State (placeholder)
        // update();

        // Render Frame
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Dark gray background
        SDL_RenderClear(renderer);

        // Draw game objects here...

        SDL_RenderPresent(renderer);
    }

    // 4. Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}