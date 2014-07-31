#include <iostream>

#include <SDL/SDL.h>
#include <string>

using namespace std;

class Pc
{
public:
    SDL_Rect loc; // location on the screen in pixels

    int width, height;

    float speed_x = 0, speed_y = 0;

    char direction = 'd';
    string bmp;

    SDL_Surface *picture;

    Pc();
    SDL_Surface *load_one_pic(string pic_bmp);
    void load(SDL_Surface *s);
    void draw(SDL_Surface *s);
    void freeSurface();

};


