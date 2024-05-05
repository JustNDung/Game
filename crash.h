#ifndef CRASH_H_INCLUDED
#define CRASH_H_INCLUDED
#include <bits/stdc++.h>
#include "defs.h"
#include "snake.h"
#include "graphics.h"

void reset_snake(){
    Snake *track = head;
    Snake *temp;
    while (track != NULL){
        temp = track;
        track = track -> next;
        free (temp);
    }
    init_snake();
    increase_snake();
    increase_snake();
    increase_snake();
}

bool detect_crash(){
    bool crash = false;

    Snake *track = head;
    if (track -> next != NULL){
        track = track -> next;
    }

    while (track != NULL){
        if (track -> x  == head -> x && track -> y == head -> y){
            crash = true;
            reset_snake();
        }
        track = track -> next;
    }
    return crash;
}

#endif // CRASH_H_INCLUDED
