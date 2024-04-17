#pragma once
#include <SDL.h>
#include <cassert>

//Screen dimension constants
const int SCREEN_WIDTH = 920;
const int SCREEN_HEIGHT = 640;

struct Point
{
    float x;
    float y;
};

void affine_transform(struct Point *points, int num_vertex, float u, float d, float alpha);
void draw_nested_figures(SDL_Surface *s, float mouse_x, float mouse_y, int num_vertex, float r, float u, float d, int n, float alpha);
void draw_figure(SDL_Surface *s, struct Point* points, int num_vertex);
void convert_coordinates(float q, struct Point* points, int num_vertex);

