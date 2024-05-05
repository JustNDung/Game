    #ifndef TIME_DURATION_H_INCLUDED
    #define TIME_DURATION_H_INCLUDED
#include "defs.h"
void time_duration_animation(SDL_Renderer *renderer, Uint32 &start_time){
        SDL_Rect rect = {10, (WINDOW_HEIGHT - RECT_HEIGHT) / 2, RECT_WIDTH, RECT_HEIGHT};

        Uint32 current_time = SDL_GetTicks();
        Uint32 elapsed_time = current_time - start_time;

        int new_rect_height = RECT_HEIGHT - elapsed_time / RECT_SPEED;
        rect.h = new_rect_height < 0 ? 0 : new_rect_height;

        SDL_SetRenderDrawColor(renderer, 250, 0, 0, 250);
        SDL_RenderFillRect(renderer, &rect);
        if (elapsed_time > RECT_SPEED * RECT_HEIGHT) {
            start_time = current_time;
        }

}

#endif // TIME_DURATION_H_INCLUDED
