#pragma once
#include <SDL.h>
#include <cassert>

//Screen dimension constants
const int SCREEN_WIDTH = 920;
const int SCREEN_HEIGHT = 640;

void draw(SDL_Surface *s, int a, int u, int d, double alpha);

int my_put_pixel(int x, int y, double alpha);
