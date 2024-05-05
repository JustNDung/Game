#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include "render_game.h"
#include "snake.h"
#include "apple.h"
#include "apple_basket.h"
#include "crash.h"
#include "map.h"
#include "over.h"
#include "highest_score.h"
#include "time_duration.h"
using namespace std;

const SDL_Rect sco {0, 0, 160, 60};

void game(Graphics &graphics, Game_state &st, const int difficulty, const int mp)
{
    srand(time(0));
    init_snake();
    increase_snake();
    increase_snake();
    increase_snake();

    vector<vector<SDL_Rect>> ob;
        switch(mp){
        case SNOWLAND:
            ob = object_for_city();
            break;
        case FOREST:
            ob = object_for_forest();
            break;
        case DESERT:
            ob = object_for_desert();
            break;
    }

    gen_apple(ob);

    Mix_Chunk *over = graphics.loadSound("Sound_Over.mp3");
    Mix_Chunk *apple_collected = graphics.loadSound("Apple_Collected.mp3");

    TTF_Font* text_font = graphics.loadFont("SnakeFont.ttf", 100);
    SDL_Color color = {255, 255, 255};

    bool quit = false;
    int apple_count = 0;

    SDL_Event event;
    bool apple_basket_generated = false;
    int score = 0;
    int highest_score = 0;

    while (!quit && st.state != OPTION_STATE && st.state != MAIN_STATE){
        Uint32 current_time = SDL_GetTicks();
        while (SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT :
                quit = true;
                break;
            case SDL_KEYUP :
                break;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym){
                case SDLK_ESCAPE :
                    quit = true;
                    break;
                case SDLK_UP :
                    head -> dir = SNAKE_UP;
                    break;
                case SDLK_DOWN :
                    head -> dir = SNAKE_DOWN;
                    break;
                case SDLK_LEFT :
                    head -> dir = SNAKE_LEFT;
                    break;
                case SDLK_RIGHT :
                    head -> dir = SNAKE_RIGHT;
                    break;
                }
                break;
            }
        }
        SDL_RenderClear(graphics.renderer);
        move_snake();

        if (detect_crash() || check_crash(ob)){

            st.state = OVER_STATE;
            graphics.play(over);
            render_gameover(graphics, st, score);

            score = 0;
            apple_count = 0;
            apple_basket_generated = false;
            gen_apple(ob);

            if (st.state == OPTION_STATE || st.state == MAIN_STATE) continue;
        }

        switch(mp){
        case SNOWLAND:
            render_snowland(graphics, ob);
            break;
        case FOREST:
            render_forest(graphics, ob);
            break;
        case DESERT:
            render_desert(graphics, ob);
            break;
        }

        if (detect_apple(score)){
            apple_count ++;
            graphics.play(apple_collected);
            apple_basket_generated = false;
            gen_apple(ob);
        }
        render_apple(graphics, graphics.renderer, INITIAL_GRID_X, INITIAL_GRID_Y);

        if (apple_count >= APPLE_FRE  && !apple_basket_generated && apple_count != 0){
            gen_apple_basket(ob);
            apple_basket_generated = true;
            apple_count = 0;
        }

        if (apple_basket_generated){
            if (detect_apple_basket(score)){
                graphics.play(apple_collected);
                apple_basket_generated = false;
                gen_apple(ob);
            }
            //time_duration_animation(graphics.renderer, start_time);
            render_apple_basket(graphics, graphics.renderer, INITIAL_GRID_X, INITIAL_GRID_Y);
        }

        Highest_Scores.read_file("highest_score.txt");
        Highest_Scores.update(mp, difficulty, score);
        Highest_Scores.write_file("highest_score.txt");

        string score_text = "Score: " + to_string(score);
        const char* score_text_char = score_text.c_str();
        SDL_Texture *Score = graphics.renderText(score_text_char, text_font, color);
        graphics.render_text_at_middle(graphics.renderer, Score, sco.y, sco.w, sco.h);

        render_grid(graphics.renderer, INITIAL_GRID_X, INITIAL_GRID_Y);
        render_snake_body(graphics, INITIAL_GRID_X, INITIAL_GRID_Y);

        SDL_SetRenderDrawColor(graphics.renderer, 0x11, 0x11, 0x11, 255);
        SDL_RenderPresent(graphics.renderer);
        SDL_Delay(difficulty);
    }
}

#endif // GAME_H_INCLUDED
