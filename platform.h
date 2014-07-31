#ifndef __platform_h__
#define __platform_h__

#include <iostream>
#include <SDL/SDL.h>
#include <string>

using namespace std;

class Platform
{
public:
    int x, y; // left end location

    int length, thickness; // in pixels

    int r, g, b; // color: red, green, blue

    string type;

    Platform();
    Platform(int _x, int _y, int _length, int _r, int _g, int _b);

    void draw(SDL_Surface *s);

};

#endif // __platform_h__
