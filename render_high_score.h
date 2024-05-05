#ifndef RENDER_HIGH_SCORE_H_INCLUDED
#define RENDER_HIGH_SCORE_H_INCLUDED
#include "defs.h"
#include "highest_score.h"
#include "map.h"
#include <SDL.h>
#include <iostream>
#include <string>

const int HighScore_width = 700;
const int HighScore_height = 200;
const int Mp_Y = 400;

void render_score_board(Graphics &graphics, HighestScores& highScores){
    SDL_RenderClear(graphics.renderer);

    SDL_Rect bck = {30, 30, 70, 70};
    SDL_Rect bck_origin = bck;

    SDL_Color text_color = { 255, 255, 255, 255 };

    TTF_Font* text_font = graphics.loadFont("SnakeFont.ttf", 150);
    SDL_Rect textRect;
    int yPosition = 50;

    SDL_Event e;
    bool quit = false;

    while (!quit){
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.x >= bck.x && e.button.x <= bck.x + bck.w && e.button.y >= bck.y && e.button.y <= bck.y + bck.h) {
                        bck.y += 15;
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_RenderClear(graphics.renderer);

        SDL_Texture *title = graphics.renderText("HIGHSCORE", text_font, text_color);
        graphics.render_text_at_middle(graphics.renderer, title, 150, HighScore_width, HighScore_height);

        SDL_Texture *Mp1 = graphics.renderText("Snow", text_font, text_color);
        graphics.renderTexture(Mp1, 90, Mp_Y, Op_width, Op_height);

        SDL_Texture *Mp2 = graphics.renderText("Forest", text_font, text_color);
        graphics.render_text_at_middle(graphics.renderer, Mp2, Mp_Y, Op_width, Op_height);

        SDL_Texture *Mp3 = graphics.renderText("Desert", text_font, text_color);
        graphics.renderTexture(Mp3, 640, Mp_Y, Op_width, Op_height);

        render_score_text(graphics, SNOWLAND, 100);
        render_score_text(graphics, FOREST, 375);
        render_score_text(graphics, DESERT, 650);

        graphics.render_texture(graphics.renderer, "Snake_Back.png", bck.x, bck.y, bck.w, bck.h);

        SDL_RenderPresent(graphics.renderer);
         if (bck.y > bck_origin.y){
            bck = bck_origin;
            quit = true;
        }
    }


    TTF_CloseFont(text_font);
}

#endif // RENDER_HIGH_SCORE_H_INCLUDED
