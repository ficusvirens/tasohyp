#include <iostream>
#include <SDL/SDL.h>
#include <vector>
#include <cmath>

#include "pc.h"
#include "platform.h"
#include "graphics.h"

using namespace std;

void putpixel(SDL_Surface *s, int x, int y, int r, int g, int b)
{
	int *scr = (int*)s->pixels;
	if ((x >= 0) && (x < s->w) && (y > 0) && (y <= s->h))
		scr[x + (s->h-y)*s->w] = SDL_MapRGB(s->format, r, g, b); // Red, Green, Blue
}

void putline(SDL_Surface *s, int x, int y, int x2, int y2, int r, int g, int b)
{
	float temp;

	if (x2 == x)
	{
		if (y < y2)
		{
			for (y = y; y < y2; y++)
			putpixel(s, x, y, r, g, b);
		}
		else
		{
			for (y = y; y > y2; y=y-1)
			putpixel(s, x, y, r, g, b);
		}
	}

	else if (y2 == y)
	{
		if (x < x2)
		{
			for (x = x; x < x2; x++)
			putpixel(s, x, y, r, g, b);
		}
		else
		{
			for (x = x; x > x2; x=x-1)
			putpixel(s, x, y, r, g, b);
		}
	}

	else
	{
		float k;
		k = float(y2-y)/float(x2-x);
		if (abs (k) <= 1)
		{
			if (x2<x)
			{
				temp = x;	x = x2; 	x2 = temp;
				temp = y;	y = y2; 	y2 = temp;
			}
            float fy = y;
			for (x=x; x<=x2; x++)
			{
				putpixel (s, round(x), round(fy), r, g, b);
				fy=fy+k;
			}
		}
		else if (abs (k) > 1)
		{
			k = float(x2-x)/float(y2-y);
			if (y2<y)
			{
				temp = x;
				x = x2;
				x2 = temp;
				temp = y;
				y = y2;
				y2 = temp;
			}
			float fx = x;
			for (y=y; y<=y2; y++)
			{
				putpixel (s, round(fx), round(y), r, g, b);
				fx=fx+k;
			}
		}
	}
}

void drawScreen(SDL_Surface *s, Pc mainCharacter, vector<Platform> platforms)
{
    if(SDL_MUSTLOCK(s))
    {
        if(SDL_LockSurface(s) < 0) return;
    }

    SDL_FillRect(s, 0, SDL_MapRGB(s->format, 123, 34, 92)); // paint the background purple


    if (platforms.size()>0) {   // draw the platforms
        for (int i=0; i<platforms.size(); i++ ) platforms[i].draw(s);
    }

    // draw the main character
    mainCharacter.draw(s);

    if(SDL_MUSTLOCK(s)) SDL_UnlockSurface(s);

   // SDL_Flip(s);
}

int checkCollisions(Pc mainCharacter, vector<Platform> platforms, int time) {

    // no collision = 0, collision up = 1, collision down = 2

    // check all the platforms
    for (int i=0; i<platforms.size(); i++ ) {
        if ((mainCharacter.loc.x+mainCharacter.width >= platforms[i].x) && ((mainCharacter.loc.x) <= (platforms[i].x+platforms[i].length)) ) {
            if (mainCharacter.speed_y > 0) {
                if((mainCharacter.loc.y+mainCharacter.collisionPointUp <= platforms[i].y) &&
                   (mainCharacter.loc.y+mainCharacter.collisionPointUp + floor(mainCharacter.speed_y*time) > platforms[i].y)) {
                    // collision up
                    return 1;
                }
            }
            else if (mainCharacter.speed_y < 0) {
                if((mainCharacter.loc.y+mainCharacter.collisionPointDown >= platforms[i].y) &&
                   (mainCharacter.loc.y+mainCharacter.collisionPointDown + floor(mainCharacter.speed_y*time) < platforms[i].y)) {
                    // collision down
                    return 2;
                }
            }
        }
    }
    // if no collisions were found, return 0
    return 0;
}

void bump(Pc mainCharacter, vector<Platform> platforms) {

}
