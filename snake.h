#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include "defs.h"
#include "graphics.h"

enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT,
};

struct snake{
    int x;
    int y;
    int dir;

    snake *next;
};

typedef struct snake Snake;
Snake *head;
Snake *tail;

void init_snake(){
    Snake *newSnake = new Snake;
    newSnake -> x =  INITIAL_SNAKE_X;
    newSnake -> y =  INITIAL_SNAKE_Y;
    newSnake -> dir = NULL;
    newSnake -> next = NULL;

    head = newSnake;
    tail = newSnake;
}

void increase_snake(){
    Snake *track = new Snake;

    switch(tail -> dir){
    case SNAKE_UP :
        track -> x = tail -> x;
        track -> y = tail -> y + 1;
        break;
    case SNAKE_DOWN :
        track -> x = tail -> x;
        track -> y = tail -> y - 1;
        break;
    case SNAKE_LEFT :
        track -> x = tail -> x + 1;
        track -> y = tail -> y;
        break;
    case SNAKE_RIGHT :
        track -> x = tail -> x - 1;
        track -> y = tail -> y;
        break;
    }
    track -> dir = tail -> dir;
    track -> next = NULL;
    tail -> next = track;
    tail = track;
}

void move_snake(){

    int prev_x = head->x;
    int prev_y = head->y;
    int prev_dir = head->dir;

    switch(head->dir){
        case SNAKE_UP:
            head->y--;
            break;
        case SNAKE_DOWN:
            head->y++;
            break;
        case SNAKE_LEFT:
            head->x--;
            break;
        case SNAKE_RIGHT:
            head->x++;
            break;
    }

    if (head -> x < 0){
        head -> x = N - 1;
    }
    else if (head -> x >= N){
        head -> x = 0;
    }
    if (head -> y < 0){
        head -> y = N - 1;
    }
    else if (head -> y >= N){
        head -> y = 0;
    }

    Snake *track = head->next;

    while(track != NULL){
        int save_x = track->x;
        int save_y = track->y;
        int save_dir = track->dir;

        track->x = prev_x;
        track->y = prev_y;
        track->dir = prev_dir;

        prev_x = save_x;
        prev_y = save_y;
        prev_dir = save_dir;

        track = track->next;
    }
}

void render_snake_body(Graphics &graphics, int x, int y) {
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 0, 255);
    int seg_size = SCREEN_WIDTH / N;

    Snake *track = head;

    while (track != NULL) {
        SDL_Rect seg;
        seg.w = seg_size;
        seg.h = seg_size;
        seg.x = x + track->x * seg_size;
        seg.y = y + track->y * seg_size;

        if (track == head) {
            switch (track->dir) {
                case SNAKE_UP:
                    graphics.render_texture(graphics.renderer, "head_up.png", seg.x, seg.y, seg.w, seg.h);
                    break;
                case SNAKE_DOWN:
                    graphics.render_texture(graphics.renderer, "head_down.png", seg.x, seg.y, seg.w, seg.h);
                    break;
                case SNAKE_LEFT:
                    graphics.render_texture(graphics.renderer, "head_left.png", seg.x, seg.y, seg.w, seg.h);
                    break;
                case SNAKE_RIGHT:
                    graphics.render_texture(graphics.renderer, "head_right.png", seg.x, seg.y, seg.w, seg.h);
                    break;
            }
        }
        else if (track == tail) {
            switch (track -> dir) {
                case SNAKE_UP:
                    graphics.render_texture(graphics.renderer, "tail_down.png", seg.x, seg.y, seg.w, seg.h);
                    break;
                case SNAKE_DOWN:
                    graphics.render_texture(graphics.renderer, "tail_up.png", seg.x, seg.y, seg.w, seg.h);
                    break;
                case SNAKE_LEFT:
                    graphics.render_texture(graphics.renderer, "tail_right.png", seg.x, seg.y, seg.w, seg.h);
                    break;
                case SNAKE_RIGHT:
                    graphics.render_texture(graphics.renderer, "tail_left.png", seg.x, seg.y, seg.w, seg.h);
                    break;
            }
        }
        else {
            switch (track->dir) {
                case SNAKE_UP:
                case SNAKE_DOWN:
                    if (track->next->dir == SNAKE_LEFT && track->dir == SNAKE_UP) {
                        graphics.render_texture(graphics.renderer, "body_topright.png", seg.x, seg.y, seg.w, seg.h);
                    }
                    else if (track->next->dir == SNAKE_RIGHT && track->dir == SNAKE_UP) {
                        graphics.render_texture(graphics.renderer, "body_topleft.png", seg.x, seg.y, seg.w, seg.h);
                    }
                    else if (track->next->dir == SNAKE_LEFT && track->dir == SNAKE_DOWN) {
                        graphics.render_texture(graphics.renderer, "body_bottomright.png", seg.x, seg.y, seg.w, seg.h);
                    }
                    else if (track->next->dir == SNAKE_RIGHT && track->dir == SNAKE_DOWN) {
                        graphics.render_texture(graphics.renderer, "body_bottomleft.png", seg.x, seg.y, seg.w, seg.h);
                    }
                    else {
                        graphics.render_texture(graphics.renderer, "body_vertical.png", seg.x, seg.y, seg.w, seg.h);
                    }
                    break;
                case SNAKE_LEFT:
                case SNAKE_RIGHT:
                    if (track->next->dir == SNAKE_UP && track->dir == SNAKE_LEFT) {
                        graphics.render_texture(graphics.renderer, "body_bottomleft.png", seg.x, seg.y, seg.w, seg.h);
                    }
                    else if (track->next->dir == SNAKE_DOWN && track->dir == SNAKE_LEFT) {
                        graphics.render_texture(graphics.renderer, "body_topleft.png", seg.x, seg.y, seg.w, seg.h);
                    }
                    else if (track->next->dir == SNAKE_UP && track->dir == SNAKE_RIGHT) {
                        graphics.render_texture(graphics.renderer, "body_bottomright.png", seg.x, seg.y, seg.w, seg.h);
                    }
                    else if (track->next->dir == SNAKE_DOWN && track->dir == SNAKE_RIGHT) {
                        graphics.render_texture(graphics.renderer, "body_topright.png", seg.x, seg.y, seg.w, seg.h);
                    }
                    else {
                        graphics.render_texture(graphics.renderer, "body_horizontal.png", seg.x, seg.y, seg.w, seg.h);
                    }
                    break;
            }
        }
        track = track->next;
    }
}
#endif // SNAKE_H_INCLUDED
