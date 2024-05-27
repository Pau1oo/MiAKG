#pragma once
#include <SDL.h>
#include <cassert>
#include <conio.h>
#include <stdlib.h>

//Screen dimension constants
const int SCREEN_WIDTH = 920;
const int SCREEN_HEIGHT = 640;

struct Point
{
    int x;
    int y;
    int b0;
    int b1;
    int b2;
    int b3;
};

void input(int* width, int* height);
void initialize_points(struct Point* points, int num_vertex, int r);
void draw_figure(SDL_Surface *s, struct Point* points, int num_vertex);
void assign_code(struct Point *point, int *borders);
void draw_vis_line(SDL_Surface *s, struct Point* points, int num_vertex);
void affine_transform(struct Point* points, int num_vertex, float shift_x, float shift_y, float alpha);
void draw(SDL_Surface *s, int width, int height, int r, int x_square, int y_square, int x_triangle, int y_triangle, float alpha, float beta);
void cohen_Sutherland(struct Point* points, int num_vertex, struct Point* invis_line_points, struct Point* vis_line_points, int* borders);
