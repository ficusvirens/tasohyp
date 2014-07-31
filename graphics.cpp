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
	if ((x >= 0) && (x < s->w) && (y >= 0) && (y < s->h))
		scr[x + y*s->w] = SDL_MapRGB(s->format, r, g, b); // Red, Green, Blue
}

void putline(SDL_Surface *s, int x, int y, int x2, int y2, int r, int g, int b)
{
	float temp;

	if (x2 == x)
	{
		if (y < y2)
		{
			for (y = y; y < y2; y++)
			putpixel(s, round(x), round(y), r, g, b);
		}
		else
		{
			for (y = y; y > y2; y=y-1)
			putpixel(s, round(x), round(y), r, g, b);
		}
	}

	else if (y2 == y)
	{
		if (x < x2)
		{
			for (x = x; x < x2; x++)
			putpixel(s, round(x), round(y), r, g, b);
		}
		else
		{
			for (x = x; x > x2; x=x-1)
			putpixel(s, round(x), round(y), r, g, b);
		}
	}

	else
	{
		float k;
		k = (y2-y)/(x2-x);
		if (abs (k) <= 1)
		{
			if (x2<x)
			{
				temp = x;	x = x2; 	x2 = temp;
				temp = y;	y = y2; 	y2 = temp;
			}

			for (x=x; x<=x2; x++)
			{
				putpixel (s, round(x), round(y), r, g, b);
				y=y+k;
			}
		}
		else if (abs (k) > 1)
		{
			k = (x2-x)/(y2-y);
			if (y2<y)
			{
				temp = x;
				x = x2;
				x2 = temp;
				temp = y;
				y = y2;
				y2 = temp;
			}
			for (y=y; y<=y2; y++)
			{
				putpixel (s, round(x), round(y), r, g, b);
				x=x+k;
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


    if (platforms.size()>0)   // draw the platforms
    {
        for (int i=platforms.size(); i>0; i-- ) platforms[i-1].draw(s);
    }

    // draw the main character
    mainCharacter.draw(s);

    if(SDL_MUSTLOCK(s)) SDL_UnlockSurface(s);

    SDL_Flip(s);
}

