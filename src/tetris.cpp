/*Copyright (c) 2012, winterdx <winterdx@gmail.com>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.*/

#include <string>
#include <sstream>

#ifdef WIN32
#include "SDL.h"
#else
#include "SDL/SDL.h"
#endif

#ifdef WIN32
#include "SDL_ttf.h"
#elif __APPLE__
#include "SDL_ttf/SDL_ttf.h"
#else
#include "SDL/SDL_ttf.h"
#endif
#include "game.h"

const int BOX_SIDE = 20;
const int TARGET_FPS = 30;
const int FRAME_TIME = 1000/TARGET_FPS;
const int DEFAULT_TIME_FALL = 800;
const int SPEED_UP_PER_POINT = 10;
const int TIME_MOVE = 120;
const SDL_Color TEXT_COLOR = {255, 255, 255};
SDL_Surface *screen;

void draw_sdl(std::list<Coord>, COLOR); 
void show_lose();
int init_sdl(TTF_Font **font, SDL_Surface **msg);

int main (int argc, char **argv) {
    TTF_Font *font;
    SDL_Surface *msg;
    bool lose = false;
    int points = 0;

    //Init sdl
    if (!init_sdl(&font, &screen)) {
        return 1;
    }

    //Init tetris
    
    //List for the "map" rectangles
    std::list<Rectangle*> rectangles;
    ini_blocks(rectangles);

    //List for the blocks
    std::list<Block*> blocks;
    Block *current_block = new_block();
    blocks.push_back(current_block);


    SDL_Event event;

    
    //Get state of the keyboard
    Uint8 *keystate = SDL_GetKeyState(0);

    //Time for a block to fall 1 square
    int time_fall = DEFAULT_TIME_FALL;
    int last_fall = SDL_GetTicks();

    //Min time between moves
    int last_move = SDL_GetTicks();
    
    //Time when the last frame was printed
    int last_frame = SDL_GetTicks();
    bool finish = false;
    while (!finish) {

        //See if a new block is needed
        if (!Block::moving_block() || !current_block) {
            current_block = new_block();
            //Check if the game is finished
            if (current_block->check_collides()) {
                lose = true;
                break;
            }
            blocks.push_back(current_block);
        }

        //Move blocks
        int current_time = SDL_GetTicks();
        if (current_time - last_fall >= time_fall) {
            last_fall = current_time;
            advance_blocks(blocks);
        }
        //Detect keypress
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                finish = true;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    finish = true;
                } else if (event.key.keysym.sym == SDLK_LEFT) {
                    current_block->move_left();
                    last_move = current_time;
                } else if (event.key.keysym.sym == SDLK_RIGHT) {
                    current_block->move_right();
                    last_move = current_time;
                } else if (event.key.keysym.sym == SDLK_UP) {
                    current_block->rotate();
                    last_move = current_time;
                }
            }
        }
        //Repeat keypress
        if (current_block) {
            if (current_time - last_move >= TIME_MOVE) {
                last_move = current_time;
                if (keystate[SDLK_LEFT])
                    current_block->move_left();
                if (keystate[SDLK_RIGHT])
                    current_block->move_right();
                if (keystate[SDLK_UP])
                    current_block->rotate();
            }

            if (keystate[SDLK_DOWN])
                current_block->move_down();
        }

        //Clean full rows
        points += clean_rows(blocks);
        time_fall = DEFAULT_TIME_FALL - points * SPEED_UP_PER_POINT;
        delete_empty_blocks(blocks);
        //If the current block has been erased, set it to 0
        bool current_found = false;
        for (std::list<Block*>::const_iterator i = blocks.begin(); i != blocks.end(); ++i)
            if (*i == current_block) {
                current_found = true;
                break;
            }
        if (!current_found)
            current_block = 0;


        //Clean screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        //Draw elements
        draw_rectangles(rectangles, draw_sdl);
        draw_blocks(blocks, draw_sdl);

        //Draw points
        std::stringstream messagestream;
        messagestream << points;
        std::string message = messagestream.str();
        msg = TTF_RenderText_Solid(font, message.c_str(), TEXT_COLOR);
        SDL_Rect destination;
        destination.x = 400;
        destination.y = 10;
        SDL_BlitSurface(msg, 0, screen, &destination);
        SDL_Flip(screen);

        //Slow framerate
        current_time = SDL_GetTicks();
        if (current_time - last_frame < FRAME_TIME)
            SDL_Delay(FRAME_TIME - (current_time - last_frame));
        last_frame = current_time;
    }

    if (lose) {
        show_lose();
    }

    //Free all
    SDL_FreeSurface(msg);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

int init_sdl(TTF_Font **font, SDL_Surface **screen) {
    //Init sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        fprintf(stderr, "Error starting SDL\n");
        return 0;
    }

    //Init sdl_ttf
    if (TTF_Init() == -1) {
        fprintf(stderr, "Error starting SDL_ttf\n");
        return 0;
    }

#ifdef WIN32
    *font = TTF_OpenFont("resources/arial.ttf", 28);
#else
    *font = TTF_OpenFont("../src/resources/arial.ttf", 28);
#endif
    if (!*font) {
        TTF_Quit();
        SDL_Quit();
        fprintf(stderr, "Error opening font\n");
        return 0;
    }

    *screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!*screen) {
        TTF_CloseFont(*font);
        TTF_Quit();
        SDL_Quit();
        fprintf(stderr, "Error starting video\n");
        return 0;
    }
    return 1;
}

void show_lose() {
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));
    SDL_Surface *tmp;
    SDL_Surface *lose;
#ifdef WIN32
    tmp = SDL_LoadBMP("resources/lose.bmp");
#else
    tmp = SDL_LoadBMP("../src/resources/lose.bmp");
#endif
    if (!tmp)
        return;
    lose = SDL_DisplayFormat(tmp);
    if (!lose)
        return;
    SDL_FreeSurface(tmp);
    SDL_BlitSurface(lose, 0, screen, 0);
    SDL_Flip(screen);
    SDL_Delay(1000);
    SDL_FreeSurface(lose);
}

void draw_sdl(std::list<Coord> coords, COLOR color) {
    for (std::list<Coord>::const_iterator i = coords.begin(); i != coords.end(); ++i) {
        SDL_Rect rect;
        rect.x = i->x * BOX_SIDE;
        rect.y = i->y * BOX_SIDE;
        rect.w = BOX_SIDE-1;
        rect.h = BOX_SIDE-1;
        Uint32 c;
        switch (color) {
            case GREY:
                c = SDL_MapRGB(screen->format, 160, 160, 160);
                break;
            case CYAN:
                c = SDL_MapRGB(screen->format, 0, 240, 240);
                break;
            case BLUE:
                c = SDL_MapRGB(screen->format, 0, 0, 240);
                break;
            case ORANGE:
                c = SDL_MapRGB(screen->format, 240, 160, 0);
                break;
            case YELLOW:
                c = SDL_MapRGB(screen->format, 240, 240, 0);
                break;
            case GREEN:
                c = SDL_MapRGB(screen->format, 0, 240, 0);
                break;
            case PURPLE:
                c = SDL_MapRGB(screen->format, 160, 0, 240);
                break;
            case RED:
                c = SDL_MapRGB(screen->format, 240, 0, 0);
                break;
            default:
                c = SDL_MapRGB(screen->format, 0, 0, 0);
                break;
        }
        SDL_FillRect(screen, &rect, c);
    }
}
