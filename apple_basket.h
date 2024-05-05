#ifndef APPLE_BASKET_H_INCLUDED
#define APPLE_BASKET_H_INCLUDED
#include "defs.h"
#include "graphics.h"
#include "apple.h"
#include "map.h"
#include "snake.h"
#include <bits/stdc++.h>
using namespace std;

struct apple_basket{
    int x;
    int y;
};
apple_basket Apple_Basket;

void gen_apple_basket(vector<vector<SDL_Rect>> ob){
    bool in_snake;
    bool in_apple;
    bool in_object;
    do {
        in_apple = false;
        in_snake = false;
        in_object = false;

        Apple_Basket.x = rand() % N;
        Apple_Basket.y = rand() % N;

        if(Apple_Basket.x == Apple.x && Apple_Basket.y == Apple.y){
            in_apple = true;
        }

        for(int i = 0; i < ob.size(); i++){
            for(int j = 0; j < ob[i].size(); j++){
                if(Apple_Basket.x == ob[i][j].x && Apple_Basket.y == ob[i][j].y){
                    in_object = true;
                    break;
                }
            }
        }

        Snake *track = head;

        while (track != NULL){
             if(track -> x == Apple_Basket.x && track -> y == Apple_Basket.y){
                  in_snake = true;
                  break;
             }
             track = track -> next;
        }
    }
    while (in_snake || in_object || in_apple);
}

void render_apple_basket(Graphics graphics, SDL_Renderer *renderer, int x, int y){
    SDL_Texture *apple_basket = graphics.loadTexture("apple_basket.png");

    SDL_Rect app;
    app.w = OBJECT_SIZE;
    app.h = OBJECT_SIZE;
    app.x = x + Apple_Basket.x * OBJECT_SIZE;
    app.y = y + Apple_Basket.y * OBJECT_SIZE;

    SDL_RenderCopy(renderer, apple_basket, NULL, &app);
    SDL_DestroyTexture(apple_basket);
}

bool detect_apple_basket(int &score){
    bool crash = false;
    if (head -> x == Apple_Basket.x && head -> y == Apple_Basket.y){
        crash = true;
        score += APPLEBASKET_SCORE;

        increase_snake();
        increase_snake();
        increase_snake();
        increase_snake();
        increase_snake();
    }
    return crash;
}

#endif // APPLE_BASKET_H_INCLUDED
