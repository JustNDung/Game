#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "option.h"
#include "defs.h"
#include "graphics.h"
#include "snake.h"
#include "bits/stdc++.h"
using namespace std;

struct Object{
    SDL_Rect ob;
};

vector<vector<SDL_Rect>> object_for_city(){
    vector <vector<SDL_Rect>> storage;
    vector <SDL_Rect> tree;
    vector <SDL_Rect> stone;

    Object object;
    object.ob.w = OBJECT_SIZE;
    object.ob.h = OBJECT_SIZE;

    for(int y = 4; y <= 15; y++){
        for(int x = 4; x <= 15; x++){
            if((y == 4 || y == 15 || x == 4 || x == 15) && y != 8 && y != 11){
                object.ob.x = x;
                object.ob.y = y;
                tree.push_back(object.ob);
            }
        }
    }

    object.ob.x = 2;
    object.ob.y = 2;
    stone.push_back(object.ob);

    object.ob.x = 2;
    object.ob.y = 17;
    stone.push_back(object.ob);

    object.ob.x = 17;
    object.ob.y = 2;
    stone.push_back(object.ob);

    object.ob.x = 17;
    object.ob.y = 17;
    stone.push_back(object.ob);

    storage.push_back(tree);
    storage.push_back(stone);

    return storage;
}

void render_snowland(Graphics &graphics, vector<vector<SDL_Rect>> ob){
    graphics.render_texture(graphics.renderer, "snowland.jpg", INITIAL_GRID_X, INITIAL_GRID_Y, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Texture *tree_texture = graphics.loadTexture("Snow_Tree.png");
    SDL_Texture *stone_texture = graphics.loadTexture("Snow_Rock.png");

    for(int i = 0; i < ob[0].size(); i++){
        ob[0][i].x = INITIAL_GRID_X + ob[0][i].x * OBJECT_SIZE;
        ob[0][i].y = INITIAL_GRID_Y + ob[0][i].y * OBJECT_SIZE;
        SDL_RenderCopy(graphics.renderer, tree_texture, NULL, &ob[0][i]);
    }

    for(int i = 0; i < ob[1].size(); i++){
        ob[1][i].x = INITIAL_GRID_X + ob[1][i].x * OBJECT_SIZE;
        ob[1][i].y = INITIAL_GRID_Y + ob[1][i].y * OBJECT_SIZE;
        SDL_RenderCopy(graphics.renderer, stone_texture, NULL, &ob[1][i]);
    }

    SDL_DestroyTexture(tree_texture);
    SDL_DestroyTexture(stone_texture);
}

vector<vector<SDL_Rect>> object_for_forest(){
    vector <vector<SDL_Rect>> storage;
    vector <SDL_Rect> tree;
    vector <SDL_Rect> stone;

    Object object;
    object.ob.w = OBJECT_SIZE;
    object.ob.h = OBJECT_SIZE;

    for(int y = 4; y <= 15; y++){
        for(int x = 4; x <= 15; x++){
            if((y == 4 || y == 15 || x == 4 || x == 15) && x != 8 && x != 9 && x != 10 && x != 11 && y != 8 && y != 9 && y != 10 && y != 11){
                object.ob.x = x;
                object.ob.y = y;
                tree.push_back(object.ob);
            }
        }
    }

    for(int y = 8; y <= 11; y++){
        object.ob.x = 2;
        object.ob.y = y;
        stone.push_back(object.ob);
    }

    for(int y = 8; y <= 11; y++){
        object.ob.x = 17;
        object.ob.y = y;
        stone.push_back(object.ob);
    }

    storage.push_back(tree);
    storage.push_back(stone);

   return storage;
}

void render_forest(Graphics &graphics, vector<vector<SDL_Rect>> ob){
    graphics.render_texture(graphics.renderer, "forest.jpg", INITIAL_GRID_X, INITIAL_GRID_Y, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Texture *tree_texture = graphics.loadTexture("Forest_Tree.png");
    SDL_Texture *stone_texture = graphics.loadTexture("Forest_Rock.png");

    for(int i = 0; i < ob[0].size(); i++){
        ob[0][i].x = INITIAL_GRID_X + ob[0][i].x * OBJECT_SIZE;
        ob[0][i].y = INITIAL_GRID_Y + ob[0][i].y * OBJECT_SIZE;
        SDL_RenderCopy(graphics.renderer, tree_texture, NULL, &ob[0][i]);
    }

    for(int i = 0; i < ob[1].size(); i++){
        ob[1][i].x = INITIAL_GRID_X + ob[1][i].x * OBJECT_SIZE;
        ob[1][i].y = INITIAL_GRID_Y + ob[1][i].y * OBJECT_SIZE;
        SDL_RenderCopy(graphics.renderer, stone_texture, NULL, &ob[1][i]);
    }

    SDL_DestroyTexture(tree_texture);
    SDL_DestroyTexture(stone_texture);
}

vector<vector<SDL_Rect>> object_for_desert(){
    vector <vector<SDL_Rect>> storage;
    vector <SDL_Rect> tree;
    vector <SDL_Rect> stone;

    Object object;
    object.ob.w = OBJECT_SIZE;
    object.ob.h = OBJECT_SIZE;

    for(int x = 4; x <= 6; x++){
        object.ob.x = x;
        object.ob.y = 4;
        stone.push_back(object.ob);
    }

    for(int x = 13; x <= 15; x++){
        object.ob.x = x;
        object.ob.y = 4;
        stone.push_back(object.ob);
    }

    for(int x = 5; x <= 7; x++){
        object.ob.x = x;
        object.ob.y = 6;
        stone.push_back(object.ob);
    }

    for(int x = 12; x <= 14; x++){
        object.ob.x = x;
        object.ob.y = 6;
        stone.push_back(object.ob);
    }

    for(int x = 4; x <= 6; x++){
        object.ob.x = x;
        object.ob.y = 15;
        stone.push_back(object.ob);
    }

    for(int x = 13; x <= 15; x++){
        object.ob.x = x;
        object.ob.y = 15;
        stone.push_back(object.ob);
    }

    for(int x = 5; x <= 7; x++){
        object.ob.x = x;
        object.ob.y = 13;
        stone.push_back(object.ob);
    }

    for(int x = 12; x <= 14; x++){
        object.ob.x = x;
        object.ob.y = 13;
        stone.push_back(object.ob);
    }

    object.ob.x = 6;
    object.ob.y = 8;
    tree.push_back(object.ob);

    object.ob.x = 6;
    object.ob.y = 11;
    tree.push_back(object.ob);

    object.ob.x = 13;
    object.ob.y = 8;
    tree.push_back(object.ob);

    object.ob.x = 13;
    object.ob.y = 11;
    tree.push_back(object.ob);


    object.ob.x = 2;
    object.ob.y = 2;
    tree.push_back(object.ob);

    object.ob.x = 17;
    object.ob.y = 17;
    tree.push_back(object.ob);

    object.ob.x = 2;
    object.ob.y = 17;
    tree.push_back(object.ob);

    object.ob.x = 17;
    object.ob.y = 2;
    tree.push_back(object.ob);

   storage.push_back(stone);
   storage.push_back(tree);

   return storage;

}

void render_desert(Graphics &graphics, vector<vector<SDL_Rect>> ob){
    graphics.render_texture(graphics.renderer, "desert.png", INITIAL_GRID_X, INITIAL_GRID_Y, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Texture *stone_texture = graphics.loadTexture("Desert_Rock.png");
    SDL_Texture *tree_texture = graphics.loadTexture("Desert_Tree.png");

    for(int i = 0; i < ob[0].size(); i++){
        ob[0][i].x = INITIAL_GRID_X + ob[0][i].x * OBJECT_SIZE;
        ob[0][i].y = INITIAL_GRID_Y + ob[0][i].y * OBJECT_SIZE;
        SDL_RenderCopy(graphics.renderer, stone_texture, NULL, &ob[0][i]);
    }

    for(int i = 0; i < ob[1].size(); i++){
        ob[1][i].x = INITIAL_GRID_X + ob[1][i].x * OBJECT_SIZE;
        ob[1][i].y = INITIAL_GRID_Y + ob[1][i].y * OBJECT_SIZE;
        SDL_RenderCopy(graphics.renderer, tree_texture, NULL, &ob[1][i]);
    }

    SDL_DestroyTexture(tree_texture);
    SDL_DestroyTexture(stone_texture);
}

bool check_crash(vector<vector<SDL_Rect>> ob){
    for(int i = 0; i < ob.size(); i++){
        for(int j = 0; j < ob[i].size(); j++){
            if (head -> x == ob[i][j].x && head -> y == ob[i][j].y){
                return true;
            }
        }
    }
    return false;
}



#endif // MAP_H_INCLUDED
