#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include "render_game.h"
#include "snake.h"
#include "apple.h"
#include "crash.h"
#include "option.h"
#include "highest_score.h"
#include "render_high_score.h"
using namespace std;

const int Snake_width = 700;
const int Snake_height = 180;

int main(int argc, char *argv[]){
    Graphics graphics;
    graphics.init();

    Game_state st;
    st.state = OPTION_STATE;

    TTF_Font* text_font = graphics.loadFont("SnakeFont.ttf", 150);
    SDL_Color text_color = { 255, 255, 255};

    SDL_Rect start = {250, 450, 150, 150};
    SDL_Rect start_origin = start;

    SDL_Rect high_score = {500, 450, 150, 150};
    SDL_Rect high_score_origin = high_score;

    Mix_Chunk *button_press = graphics.loadSound("Button_Press.mp3");

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.x >= start.x && e.button.x <= start.x + start.w && e.button.y >= start.y && e.button.y <= start.y + start.h) {
                        start.y += 15;
                    }
                    if (e.button.x >= high_score.x && e.button.x <= high_score.x + high_score.w && e.button.y >= high_score.y && e.button.y <= high_score.y + high_score.h) {
                        high_score.y += 15;
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
        SDL_RenderClear(graphics.renderer);

        graphics.render_texture(graphics.renderer, "menu.jpg", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

        SDL_Texture *title = graphics.renderText("SnakeGame", text_font, text_color);
        graphics.render_text_at_middle(graphics.renderer, title, 270, Snake_width, Snake_height);

        graphics.render_texture(graphics.renderer, "Snake_Play.png", start.x, start.y, start.w, start.h);
        graphics.render_texture(graphics.renderer, "Snake_Highest.png", high_score.x, high_score.y, high_score.w, high_score.h);
        SDL_RenderPresent(graphics.renderer);

        if (start.y > start_origin.y) {
            start = start_origin;
            graphics.play(button_press);
            displayOptions(graphics, st);
        }

        if (high_score.y > high_score_origin.y) {
            high_score = high_score_origin;
            graphics.play(button_press);
            render_score_board(graphics, Highest_Scores);
        }

    }
    TTF_CloseFont(text_font);
    return 0;
}
