#ifndef APPLE_H_INCLUDED
#define APPLE_H_INCLUDED
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "snake.h"
using namespace std;

struct apple{
    int x;
    int y;
};

apple Apple;

void gen_apple(vector<vector<SDL_Rect>> ob){
    bool in_snake;
    bool in_object;
    do {
        in_snake = false;
        in_object = false;
        Apple.x = rand() % N;
        Apple.y = rand() % N;

        for(int i = 0; i < ob.size(); i++){
            for(int j = 0; j < ob[i].size(); j++){
                if(Apple.x == ob[i][j].x && Apple.y == ob[i][j].y){
                    in_object = true;
                    break;
                }
            }
        }

        Snake *track = head;

        while (track != NULL){
             if(track -> x == Apple.x && track -> y == Apple.y){
                  in_snake = true;
                  break;
             }
             track = track -> next;
         }
    }
    while (in_snake || in_object);
}

void render_apple(Graphics graphics, SDL_Renderer *renderer, int x, int y){
    SDL_Texture *apple = graphics.loadTexture("apple.png");

    SDL_Rect app;
    app.w = OBJECT_SIZE;
    app.h = OBJECT_SIZE;
    app.x = x + Apple.x * OBJECT_SIZE;
    app.y = y + Apple.y * OBJECT_SIZE;

    SDL_RenderCopy(renderer, apple, NULL, &app);
    SDL_DestroyTexture(apple);
}

bool detect_apple(int &score){
    bool crash = false;
    if (head -> x == Apple.x && head -> y == Apple.y){
        crash = true;
        score += APPLE_SCORE;
        increase_snake();
    }
    return crash;
}

#endif // APPLE_H_INCLUDED
