#pragma once
#include <SDL.h>
#include <cassert>

//Screen dimension constants
const int SCREEN_WIDTH = 920;
const int SCREEN_HEIGHT = 640;

void affine_transform(float* x, float* y, float u, float d, float alpha);
void draw_square(SDL_Surface *s, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void draw(SDL_Surface *s, float r, float u, float d, float alpha);
