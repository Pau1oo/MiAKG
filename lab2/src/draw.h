#pragma once
#include <SDL.h>
#include <cassert>

//Screen dimension constants
const int SCREEN_WIDTH = 920;
const int SCREEN_HEIGHT = 640;

void convert_coordinates5(float q, float *x1, float *y1, float *x2, float *y2, float *x3, float *y3, float *x4, float *y4, float *x5, float *y5);
void convert_coordinates4(float q, float *x1, float *y1, float *x2, float *y2, float *x3, float *y3, float *x4, float *y4);
void convert_coordinates3(float q, float *x1, float *y1, float *x2, float *y2, float *x3, float *y3);
void affine_transform(float *x, float *y, float u, float d, float alpha);
void draw_pentagon(SDL_Surface *s, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5);
void draw_square(SDL_Surface *s, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void draw_triangle(SDL_Surface *s, float x1, float y1, float x2, float y2, float x3, float y3);
void draw_nested_squares(SDL_Surface *s, float r, float u, float d, int n, float alpha);
void draw_nested_triangles(SDL_Surface *s, float r, float u, float d, int n, float alpha);
void draw_nested_pentagons(SDL_Surface *s, float r, float u, float d, int n, float alpha);

