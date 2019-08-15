#include <iostream>
#include <string>
#include <SDL/SDL.h>

#include "pc.h"

#define WIDTH 640
#define HEIGHT 480

using namespace std;

Pc::Pc(){
    bmp = "lumikko.bmp";

    // let's start from the left bottom corner
    loc.x = 0;
    loc.y = 0;

}

// this is useful as we get more images for the main character (going left/right/up etc.)
SDL_Surface *Pc::load_one_pic(string pic_bmp) {

    SDL_Surface *pic;

    // return if it's not a bmp-file
    if (pic_bmp.substr(pic_bmp.length()-4,4) == ".bmp") {
        pic = SDL_LoadBMP(pic_bmp.c_str());
    } else {
        cout << "Could not load file " << pic_bmp << " (wrong type)." << endl;
        return NULL;
    }

    if (!pic) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return NULL;
    }

    // set the background transparent
    SDL_SetColorKey(pic, SDL_SRCCOLORKEY, SDL_MapRGB(pic->format, 255, 0, 255));

    width = pic->w;
    height = pic->h;

    collisionPointDown = 7;
    collisionPointUp = height;

    return pic;
}

void Pc::load(SDL_Surface *s) {
    // load the lumikko image
    picture = load_one_pic(bmp);

    // now we would load all the other images of the main character, too, but we don't have them yet
}

void Pc::draw(SDL_Surface *s) {
    // this will be a much more complicated function as we get the other images...
    SDL_Rect temp;
    temp.x = loc.x;
    temp.y = s->h-loc.y-height;
    SDL_BlitSurface(picture, 0, s, &temp);
}

void Pc::freeSurface() {
    SDL_FreeSurface(picture);
}

void Pc::jump() {
    speed_y += .8;
}

void Pc::go(int time) {
    // location on the screen

    loc.x += speed_x*time;
    loc.y += speed_y*time;
    speed_y -= g;  // gravitation


    // stay on the screen
    if (loc.x > WIDTH-width) {
        loc.x = WIDTH-width;
        speed_x = 0;
    }
    if (loc.x < 0) {
        loc.x = 0;
        speed_x = 0;
    }
    if (loc.y > HEIGHT-height) {
        loc.y = HEIGHT-height;
        speed_y = 0;
    }
    if (loc.y < 0) {
        loc.y = 0;
        speed_y = 0;
    }

    cout << "speed y " << speed_y << endl;

}
