#ifndef __graphics_h__
#define __graphics_h__


#include <SDL/SDL.h>
#include <vector>

#include "platform.h"
#include "pc.h"

using namespace std;

void putpixel(SDL_Surface *s, int x, int y, int r, int g, int b); // draw a single pixel to (x, y)

void putline(SDL_Surface *s, int x, int y, int x2, int y2, int r, int g, int b); // draw a line between (x, y) and (x2, y2)

void drawScreen(SDL_Surface *s, Pc mainCharacter, vector<Platform> platforms);

int checkCollisions(Pc mainCharacter, vector<Platform> platforms, int time);
void bump(Pc mainCharacter, vector<Platform> platforms);


#endif // __graphics_h__
