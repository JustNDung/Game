#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "game.h"
#include "graphics.h"
#include "map.h"

const int GameMode_width = 650;
const int GameMode_height = 150;

const int Op_width = 170;
const int Op_height = 70;

const int Diff_width = 280;
const int Diff_height = 70;

const int Diff_y = 360;
const int Map_y = 510;

const int Map_width = 170;
const int Map_height = 70;

void displayOptions(Graphics &graphics, Game_state &st) {
    SDL_Event e;

    SDL_Rect play = {300, 600, 230, 100};
    SDL_Rect playOrigin = play;

    SDL_Rect bck = {30, 30, 70, 70};
    SDL_Rect bck_origin = bck;

    TTF_Font* text_font = graphics.loadFont("SnakeFont.ttf", 100);
    TTF_Font* mode_font = graphics.loadFont("SnakeFont.ttf", 60);

    SDL_Color normal_color = {255, 255, 255};
    SDL_Color diff_color = {255, 0, 0};
    SDL_Color map_color = {255, 255, 0};

    Mix_Chunk *click_menu = graphics.loadSound("Click_Menu.mp3");
    Mix_Chunk *game_start = graphics.loadSound("Game_Start.mp3");

    bool quit = false;

    bool op1_selected = false;
    bool op2_selected = false;
    bool op3_selected = false;

    bool Mp1_selected = false;
    bool Mp2_selected = false;
    bool Mp3_selected = false;

    int difficulty = 0;
    int mp;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.x >= 90 && e.button.x <= 90 + Op_width && e.button.y >= Diff_y && e.button.y <= Diff_y + Op_height){
                        graphics.play(click_menu);
                        op1_selected = true;
                        op2_selected = false;
                        op3_selected = false;
                        difficulty = EASY;
                    }
                    if(e.button.x >= (WINDOW_WIDTH - Op_width) / 2 && e.button.x <= (WINDOW_WIDTH - Op_width) / 2 + Op_width && e.button.y >= Diff_y && e.button.y <= Diff_y + Op_height){
                        graphics.play(click_menu);
                        op1_selected = false;
                        op2_selected = true;
                        op3_selected = false;
                        difficulty = MEDIUM;
                    }
                    if(e.button.x >= 640 && e.button.x <= 640 + Op_width && e.button.y >= Diff_y && e.button.y <= Diff_y + Op_height){
                        graphics.play(click_menu);
                        op1_selected = false;
                        op2_selected = false;
                        op3_selected = true;
                        difficulty = HARD;
                    }
                    if(e.button.x >= 90 && e.button.x <= 90 + Map_width && e.button.y >= Map_y && e.button.y <= Map_y + Map_height){
                        graphics.play(click_menu);
                        Mp1_selected = true;
                        Mp2_selected = false;
                        Mp3_selected = false;
                        mp = SNOWLAND;
                    }
                    if(e.button.x >= (WINDOW_WIDTH - Map_width) / 2 && e.button.x <= (WINDOW_WIDTH - Map_width) / 2 + Map_width && e.button.y >= Map_y && e.button.y <= Map_y + Map_height){
                        graphics.play(click_menu);
                        Mp1_selected = false;
                        Mp2_selected = true;
                        Mp3_selected = false;
                        mp = FOREST;
                    }
                    if(e.button.x >= 640 && e.button.x <= 640 + Map_width && e.button.y >= Map_y && e.button.y <= Map_y + Map_height){
                        graphics.play(click_menu);
                        Mp1_selected = false;
                        Mp2_selected = false;
                        Mp3_selected = true;
                        mp = DESERT;
                    }
                    if((op1_selected || op2_selected || op3_selected) && (Mp1_selected || Mp2_selected || Mp3_selected)) {
                        if(e.button.x >= (WINDOW_WIDTH - play.w) / 2 && e.button.x <= (WINDOW_WIDTH - play.w) / 2 + play.w && e.button.y >= play.y && e.button.y <= play.y + play.h){
                                play.y += 15;
                                st.state = RUNNING_STATE;
                        }
                    }
                    if (e.button.x >= bck.x && e.button.x <= bck.x + bck.w && e.button.y >= bck.y && e.button.y <= bck.y + bck.h) {
                        bck.y += 15;
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
        SDL_RenderClear(graphics.renderer);

        graphics.render_texture(graphics.renderer, "menu.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        SDL_Texture *GameMode = graphics.renderText("GameMode", text_font, normal_color);
        graphics.render_text_at_middle(graphics.renderer, GameMode, 160, GameMode_width, GameMode_height);

        SDL_Texture *Difficulty = graphics.renderText("Difficulty", text_font, diff_color);
        graphics.render_text_at_middle(graphics.renderer, Difficulty, 295, Diff_width, Diff_height);

        SDL_Texture *Op1 = graphics.renderText("Easy", mode_font, op1_selected ? diff_color : normal_color);
        graphics.renderTexture(Op1, 90, Diff_y, Op_width, Op_height);

        SDL_Texture *Op2 = graphics.renderText("Medium", mode_font, op2_selected ? diff_color : normal_color);
        graphics.render_text_at_middle(graphics.renderer, Op2, Diff_y, Op_width, Op_height);

        SDL_Texture *Op3 = graphics.renderText("Hard", mode_font, op3_selected ? diff_color : normal_color);
        graphics.renderTexture(Op3, 640, Diff_y, Op_width, Op_height);

        SDL_Texture *Map = graphics.renderText("Map", text_font, map_color);
        graphics.render_text_at_middle(graphics.renderer, Map, 440, Map_width, Map_height);

        SDL_Texture *Mp1 = graphics.renderText("Snow", mode_font, Mp1_selected ? map_color : normal_color);
        graphics.renderTexture(Mp1, 90, Map_y, Op_width, Op_height);

        SDL_Texture *Mp2 = graphics.renderText("Forest", mode_font, Mp2_selected ? map_color : normal_color);
        graphics.render_text_at_middle(graphics.renderer, Mp2, Map_y, Op_width, Op_height);

        SDL_Texture *Mp3 = graphics.renderText("Desert", mode_font, Mp3_selected ? map_color : normal_color);
        graphics.renderTexture(Mp3, 640, Map_y, Op_width, Op_height);

        graphics.render_texture_at_middle(graphics.renderer, "Snake_Start.png", play.x, play.y, play.w, play.h);
        graphics.render_texture(graphics.renderer, "Snake_Back.png", bck.x, bck.y, bck.w, bck.h);

        SDL_RenderPresent(graphics.renderer);

        if (bck.y > bck_origin.y){
            bck = bck_origin;
            quit = true;
        }

        if (play.y > playOrigin.y){
            play = playOrigin;
            graphics.play(game_start);
            game(graphics, st, difficulty, mp);
            quit = true;
        }
    }
}

#endif // OPTION_H_INCLUDED
