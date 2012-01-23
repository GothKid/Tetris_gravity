#include "SDL/SDL.h"
#include "game.h"

const int BOX_SIDE = 20;
SDL_Surface *screen;

void draw_sdl(std::list<Coord>, COLOR); 

int main (int argc, char **argv) {
    SDL_Surface *block;
    SDL_Surface *tmp;
    //Init sdl
    SDL_Init(SDL_INIT_EVERYTHING);

    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) {
        fprintf(stderr, "Error starting video\n");
        return 1;
    }

    //Load block
    tmp = SDL_LoadBMP("resources/block.bmp");
    if (!tmp) {
        fprintf(stderr, "Error loading image\n");
        return 1;
    }

    block = SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);
    if (!block) {
        fprintf(stderr, "Error optimizing image\n");
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

    bool finish = false;
    Uint8 *keystate = SDL_GetKeyState(0);

    //Time for a block to fall 1 square
    int time_fall = 1000;
    int last_fall = SDL_GetTicks();

    //Min time between moves
    int time_move = 100;
    int last_move = SDL_GetTicks();
    
    while (!finish) {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                finish = true;
        //See if a new block is needed
        if (!Block::is_moving() || !current_block) {
            fprintf(stderr, "Block created\n");
            current_block = new_block();
            blocks.push_back(current_block);
        }

        //Move blocks
        int current_time = SDL_GetTicks();
        if (current_time - last_fall >= time_fall) {
            last_fall = current_time;
            advance_blocks(blocks);
        }
        if (current_block) {
            if (current_time - last_move >= time_move) {
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
        clean_rows(blocks);
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
        SDL_Flip(screen);
    }

    SDL_Quit();
    return 0;
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
