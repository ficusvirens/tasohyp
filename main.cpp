#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>

#include "pc.h"

#define WIDTH 640
#define HEIGHT 480

/* TODO
    - pelihahmolle eri kuvakkeet eri suuntiin liikkumista varten (+ askellus?); koodin voi kopioida kettupelist‰
    - taso-olio, jolla voi luoda ja piirt‰‰ ruudulle erilaisia tasoja
    - piirtofunktio eli liikkuminen pit‰‰ jotenkin synkata t‰h‰n
    - hyppiminen
    - painovoima
    - jee
*/

int main ( int argc, char** argv )
{

    unsigned int ticks = 0, oldticks = 0;

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    Pc lumikko;
    lumikko.load(screen);

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
              // check for messages
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                // check for keypresses
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ){
                        case SDLK_ESCAPE:    // exit if ESCAPE is pressed
                            done = true;
                            break;
                        case SDLK_RIGHT:
                            lumikko.speed_x = .5;
                            break;
                        case SDLK_LEFT:
                            lumikko.speed_x = -.5;
                            break;
                        case SDLK_UP:
                            lumikko.speed_y = -.3;
                            break;
                        case SDLK_DOWN:
                            lumikko.speed_y = .3;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch( event.key.keysym.sym ){
                        case SDLK_RIGHT:
                            lumikko.speed_x = 0;
                            break;
                        case SDLK_LEFT:
                            lumikko.speed_x = 0;
                            break;
                        case SDLK_UP:
                            lumikko.speed_y = 0;
                            break;
                        case SDLK_DOWN:
                            lumikko.speed_y = 0;
                            break;
                        default:
                            break;
                    }
                    break;
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 123, 34, 92));

        // draw lumikko
        lumikko.draw(screen);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);

        SDL_Delay(11);
        oldticks = ticks;
        ticks = SDL_GetTicks();

        // location on the screen
        lumikko.loc.x += lumikko.speed_x*(ticks-oldticks);
        lumikko.loc.y += lumikko.speed_y*(ticks-oldticks);

        // stay on the screen
        if (lumikko.loc.x > WIDTH-lumikko.width) lumikko.loc.x = WIDTH-lumikko.width;
        if (lumikko.loc.x < 0) lumikko.loc.x = 0;
        if (lumikko.loc.y > HEIGHT-lumikko.height) lumikko.loc.y = HEIGHT-lumikko.height;
        if (lumikko.loc.y < 0) lumikko.loc.y = 0;

    } // end main loop


    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
