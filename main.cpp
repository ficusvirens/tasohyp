#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>

#include "pc.h"
#include "platform.h"
#include "graphics.h"

#define WIDTH 640
#define HEIGHT 480

/* TODO
    - pelihahmolle eri kuvakkeet eri suuntiin liikkumista varten (+ askellus?); koodin voi kopioida kettupelist‰
    - piirtofunktio eli liikkuminen pit‰‰ jotenkin synkata taso-olioihin
    - hyppiminen
    - painovoima

    VISIO
    - lumikko koettaa valloittaa koe-el‰inlabran
    - syˆ matkan varrella hiiri‰ h‰keist‰ tai irrallaan
    - pahat laboranttien k‰det vainoavat
    - karttaruutu, josta n‰kyy kentt‰valikoima
    - kun kentti‰ p‰‰see l‰pi, saa palikoita joilla edist‰‰ laboratorion valloitusta
    - l‰pi pelattujen kenttien ohi voi kulkea suvereenisti
*/

int main ( int argc, char** argv )
{
    cout << "Main alkaa!\n";

    unsigned int ticks = 0, oldticks = 0, time = 0;

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    Pc lumikko;
    lumikko.load(screen);

    // create a platform
    vector<Platform> platforms;
    Platform myPlatform(10, 50, 200, 0, 0, 0);
    platforms.push_back(myPlatform);
    Platform myOtherPlatform(300, 180, 200, 0, 0, 0);
    platforms.push_back(myOtherPlatform);

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
                            lumikko.speed_y = .3;
                            break;
                        case SDLK_DOWN:
                            lumikko.speed_y = -.3;
                            break;
                        case SDLK_SPACE:
                            lumikko.jump();
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
 //       SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 123, 34, 92));

        // draw a platform
 //       platforms[0].draw(screen);

        // draw lumikko
 //       lumikko.draw(screen);

        // draw the screen, including pc and platforms
        if (checkCollisions(lumikko, platforms, time)) lumikko.speed_y = 0;
        drawScreen(screen, lumikko, platforms);
        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);

        SDL_Delay(11);
        oldticks = ticks;
        ticks = SDL_GetTicks();
        time = ticks-oldticks;

        // update the location on screen
        lumikko.go(time);

    } // end main loop


    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
