#ifndef RENDER_GAME_H_INCLUDED
#define RENDER_GAME_H_INCLUDED
#include <bits/stdc++.h>
#include <SDL.h>
#include "defs.h"

void render_grid(SDL_Renderer *renderer, int x, int y){
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0xff, 255);
#if 0
    int cell_size = SCREEN_WIDTH / N;
    SDL_Rect cell;
    cell.w = cell_size;
    cell.h = cell_size;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cell.x = x + i * cell_size;
            cell.y = y + j * cell_size;
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
# else
    SDL_Rect outline;
    outline.x = x;
    outline.y = y;
    outline.w = SCREEN_WIDTH;
    outline.h = SCREEN_HEIGHT;

    SDL_RenderDrawRect(renderer, &outline);
#endif
}

#endif // RENDER_GAME_H_INCLUDED
