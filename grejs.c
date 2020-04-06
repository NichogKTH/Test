//
//  main.c
//  SDL Test
//
//  Created by Ernst on 2020-03-25.
//  Copyright © 2020 Ernst. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h> //To use Bool
const int WIDTH=800, HEIGTH=600;
int main(int argc, char * argv[]) {
    // insert code here...
    bool run = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL init not working");
    }
    SDL_Window *window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGTH, SDL_WINDOW_ALLOW_HIGHDPI);
    if(0 == window)
    {
        printf("%s",SDL_GetError());
        return 1;
    }
    SDL_Event windowEvent;
    while(run)
    {
        if(SDL_PollEvent(&windowEvent))
        {
            if(SDL_QUIT == windowEvent.type)
            {
                run = false;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit(); //Don't forget to quit SDL
    return 0;
}
