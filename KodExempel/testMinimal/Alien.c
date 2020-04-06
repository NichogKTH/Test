//
//  Alien.c
//  F4
//
//  Created by Jonas Wåhslén on 2016-02-26.
//  Copyright © 2016 Jonas Wåhslén. All rights reserved.
//


#include <stdlib.h>
#include "Alien.h"


#define PUBLIC /* empty */
#define PRIVATE static

PRIVATE int ALIEN_WIDTH = 15;
PRIVATE int ALIEN_HEIGHT = 15;

struct Alien_type{
    int ALIEN_POSITION_X;
    int ALIEN_POSITION_Y;
    int ALIEN_FRAME;
    int slow;
};

PUBLIC Alien createAlien(int x, int y){
    Alien s = malloc(sizeof(struct Alien_type));
    s->ALIEN_POSITION_Y = y;
    s->ALIEN_POSITION_X = x;
    s->ALIEN_FRAME = 0;
    s->slow = 1;
    return s;
}

void setY(Alien a, int y){
    a->ALIEN_POSITION_Y = y;
}


PUBLIC void setAlienPositionY(Alien a, int y){
    a->ALIEN_POSITION_Y = y;
}

PUBLIC int getAlienPositionX(Alien a){
    return a->ALIEN_POSITION_X;
}


PUBLIC int getAlienPositionY(Alien a){
    return a->ALIEN_POSITION_Y;
}

PUBLIC int getAlienWidth(){
    return ALIEN_WIDTH;
}

PUBLIC int getAlienHeight(){
    return ALIEN_HEIGHT;
}

PUBLIC int getAlienFrame(Alien a){
    return a->ALIEN_FRAME;
}


PUBLIC int AlienTickRight(Alien a){
    int collided = 0;
    if(a->slow == 5){
        if(a->ALIEN_POSITION_Y<=240){
            (a->ALIEN_POSITION_Y)++;
            a->ALIEN_FRAME = 0;
        }
        else{
            (a->ALIEN_POSITION_Y)--;
            a->ALIEN_FRAME = 0;
            collided = 1;
        }
    }else if(a->slow == 10){
        if(a->ALIEN_POSITION_Y<=240){
            (a->ALIEN_POSITION_Y)++;
            a->ALIEN_FRAME = 1;
            a->slow = 0;
        }
        else{
            (a->ALIEN_POSITION_Y)--;
            a->ALIEN_FRAME = 1;
            a->slow = 0;
            collided = 1;
            }
        
    }
    (a->slow)++;
    return collided;
}
PUBLIC int AlienTickLeft(Alien a){
    int collided = 1;
    if(a->slow == 5){
        if(a->ALIEN_POSITION_Y>=0){
            (a->ALIEN_POSITION_Y)--;
            a->ALIEN_FRAME = 0;
        }
        else{
            (a->ALIEN_POSITION_Y)++;
            a->ALIEN_FRAME = 0;
            collided = 0;
        }
    }else if(a->slow == 10){
        if(a->ALIEN_POSITION_Y>=0){
            (a->ALIEN_POSITION_Y)--;
            a->ALIEN_FRAME = 1;
            a->slow = 0;
        }
        else{
            (a->ALIEN_POSITION_Y)++;
            a->ALIEN_FRAME = 1;
            a->slow = 0;
            collided = 0;
            }
        
    }
    (a->slow)++;
    return collided;
}