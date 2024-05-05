#ifndef OVER_H_INCLUDED
#define OVER_H_INCLUDED
#include "graphics.h"
#include "defs.h"
#include "render_game.h"
#include "option.h"
#include "crash.h"
#include "SDL_ttf.h"
#include <bits/stdc++.h>
using namespace std;

const SDL_Rect game_ov {0, 150, 600, 300};
const SDL_Rect sc {0, 450, 380, 170};

void render_gameover(Graphics &graphics, Game_state &st, int score) {

    SDL_RenderClear(graphics.renderer);

    SDL_Rect S_op {150, 600, 150, 150};
    SDL_Rect S_op_origin = S_op;

    SDL_Rect S_rest {375, 600, 150, 150};
    SDL_Rect S_rest_origin = S_rest;

    SDL_Rect S_main {600, 600, 150, 150};
    SDL_Rect S_main_origin = S_main;

    TTF_Font* text_font = graphics.loadFont("SnakeFont.ttf", 100);
    SDL_Color color = {0, 0, 0};

    Mix_Chunk *button_press = graphics.loadSound("Button_Press.mp3");

    SDL_Event e;
    bool quit = false;

    reset_snake();

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.x >= S_rest.x && e.button.x <= S_rest.x + S_rest.w && e.button.y >= S_rest.y && e.button.y <= S_rest.y + S_rest.h){
                        S_rest.y += 15;
                        st.state = RUNNING_STATE;
                    }
                    if(e.button.x >= S_op.x && e.button.x <= S_op.x + S_op.w && e.button.y >= S_op.y && e.button.y <= S_op.y + S_op.h){
                        S_op.y += 15;
                        st.state = OPTION_STATE;
                    }
                    if(e.button.x >= S_main.x && e.button.x <= S_main.x + S_main.w && e.button.y >= S_main.y && e.button.y <= S_main.y + S_main.h){
                        S_main.y += 15;
                        st.state = MAIN_STATE;
                    }
                    break;
                default:
                    break;
            }
        }
        graphics.render_texture(graphics.renderer, "over_background.jpg", INITIAL_GRID_X, INITIAL_GRID_Y, SCREEN_WIDTH, SCREEN_HEIGHT);
        render_grid(graphics.renderer, INITIAL_GRID_X, INITIAL_GRID_Y);

        graphics.render_texture_at_middle(graphics.renderer, "gameover.png", game_ov.x, game_ov.y, game_ov.w, game_ov.h);
        graphics.render_texture(graphics.renderer, "Snake_Option.png", S_op.x, S_op.y, S_op.w, S_op.h);
        graphics.render_texture(graphics.renderer, "Snake_Restart.png", S_rest.x, S_rest.y, S_rest.w, S_rest.h);
        graphics.render_texture(graphics.renderer, "Snake_Main.png", S_main.x, S_main.y, S_main.w, S_main.h);

        string score_text = "Score: " + to_string(score);
        const char* score_text_char = score_text.c_str();
        SDL_Texture *Score = graphics.renderText(score_text_char, text_font, color);
        graphics.render_text_at_middle(graphics.renderer, Score, sc.y, sc.w, sc.h);

        SDL_RenderPresent(graphics.renderer);

        if (st.state == RUNNING_STATE && S_rest.y > S_rest_origin.y){
            S_rest = S_rest_origin;
            graphics.play(button_press);
            quit = true;
        }

        if (st.state == OPTION_STATE && S_op.y > S_op_origin.y){
            S_op = S_op_origin;
            graphics.play(button_press);
            quit = true;
        }

        if (st.state == MAIN_STATE && S_main.y > S_main_origin.y){
            S_main = S_main_origin;
            graphics.play(button_press);
            quit = true;
        }

    }

    TTF_CloseFont(text_font);

}

#endif // OVER_H_INCLUDED
