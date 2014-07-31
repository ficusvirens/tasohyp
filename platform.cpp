

#include <iostream>
#include <string>
#include <SDL/SDL.h>

#include "platform.h"
#include "graphics.h"

using namespace std;

Platform::Platform() {
}

Platform::Platform(int _x, int _y, int _length, int _r, int _g, int _b) {
    x = _x;
    y = _y;
    length = _length;
    r = _r;
    g = _g;
    b = _b;
}

void Platform::draw(SDL_Surface *s) {
    int x2 = x+length;
    putline(s, x, y, x2, y, r, g, b);

}

