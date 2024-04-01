
#include "draw.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define RGB32(r, g, b) static_cast<uint32_t>((((static_cast<uint32_t>(b) << 8) | g) << 8) | r)

void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  if((x > 0 && x < SCREEN_WIDTH) && (y > 0 && y < SCREEN_HEIGHT)){
  Uint32 *pixels = (Uint32 *)surface->pixels;
  pixels[(y * surface->w) + x] = pixel;
}
}

Uint32 get_pixel32(SDL_Surface *surface, int x, int y)
{
  assert(NULL != surface);
  assert(x < SCREEN_WIDTH);
  assert(y < SCREEN_HEIGHT);

  Uint32 *pixels = (Uint32 *)surface->pixels;
  return pixels[(y * surface->w) + x];
}

void draw_axis(SDL_Surface *s)
{
  for (int i = 0; i < SCREEN_WIDTH; i++)
    put_pixel32(s, i, SCREEN_HEIGHT / 2, RGB32(105, 105, 105));

  for (int j = 0; j < SCREEN_HEIGHT; j++)
    put_pixel32(s, SCREEN_WIDTH / 2, j, RGB32(105, 105, 105));
}

void draw_square(SDL_Surface *s, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x2 - x1) * t + x1;
    float y = (y2 - y1) * t + y1;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }

  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x3 - x2) * t + x2;
    float y = (y3 - y2) * t + y2;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }

  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x4 - x3) * t + x3;
    float y = (y4 - y3) * t + y3;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }

  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x1 - x4) * t + x4;
    float y = (y1 - y4) * t + y4;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }
}

void draw_triangle(SDL_Surface *s, float x1, float y1, float x2, float y2, float x3, float y3)
{
  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x2 - x1) * t + x1;
    float y = (y2 - y1) * t + y1;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }

  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x3 - x2) * t + x2;
    float y = (y3 - y2) * t + y2;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }

  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x1 - x3) * t + x3;
    float y = (y1 - y3) * t + y3;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }
}

void draw_pentagon(SDL_Surface *s, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5)
{
  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x2 - x1) * t + x1;
    float y = (y2 - y1) * t + y1;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }

  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x3 - x2) * t + x2;
    float y = (y3 - y2) * t + y2;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }

  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x4 - x3) * t + x3;
    float y = (y4 - y3) * t + y3;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }

  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x5 - x4) * t + x4;
    float y = (y5 - y4) * t + y4;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }

  for (float t = 0; t <= 1; t += 0.001)
  {
    float x = (x1 - x5) * t + x5;
    float y = (y1 - y5) * t + y5;
    put_pixel32(s, x, y, RGB32(0, 0, 0));
  }
}

void affine_transform(float *x, float *y, float u, float d, float alpha)
{
  float rotate_x = (*x) * cos(alpha) + (*y) * sin(alpha);
  float rotate_y = -(*x) * sin(alpha) + (*y) * cos(alpha);
  *x = rotate_x;
  *y = rotate_y;
  *x += u;
  *y += d;
}

void convert_coordinates5(float q, float *x1, float *y1, float *x2, float *y2, float *x3, float *y3, float *x4, float *y4, float *x5, float *y5)
{
  float new_x1 = (1 - q) * (*x1) + q * (*x2);
  float new_y1 = (1 - q) * (*y1) + q * (*y2);
  float new_x2 = (1 - q) * (*x2) + q * (*x3);
  float new_y2 = (1 - q) * (*y2) + q * (*y3);
  float new_x3 = (1 - q) * (*x3) + q * (*x4);
  float new_y3 = (1 - q) * (*y3) + q * (*y4);
  float new_x4 = (1 - q) * (*x4) + q * (*x5);
  float new_y4 = (1 - q) * (*y4) + q * (*y5);
  float new_x5 = (1 - q) * (*x5) + q * (*x1);
  float new_y5 = (1 - q) * (*y5) + q * (*y1);

  *x1 = new_x1;
  *y1 = new_y1;
  *x2 = new_x2;
  *y2 = new_y2;
  *x3 = new_x3;
  *y3 = new_y3;
  *x4 = new_x4;
  *y4 = new_y4;
  *x5 = new_x5;
  *y5 = new_y5;
}

void convert_coordinates4(float q, float *x1, float *y1, float *x2, float *y2, float *x3, float *y3, float *x4, float *y4)
{
  float new_x1 = (1 - q) * (*x1) + q * (*x2);
  float new_y1 = (1 - q) * (*y1) + q * (*y2);
  float new_x2 = (1 - q) * (*x2) + q * (*x3);
  float new_y2 = (1 - q) * (*y2) + q * (*y3);
  float new_x3 = (1 - q) * (*x3) + q * (*x4);
  float new_y3 = (1 - q) * (*y3) + q * (*y4);
  float new_x4 = (1 - q) * (*x4) + q * (*x1);
  float new_y4 = (1 - q) * (*y4) + q * (*y1);

  *x1 = new_x1;
  *y1 = new_y1;
  *x2 = new_x2;
  *y2 = new_y2;
  *x3 = new_x3;
  *y3 = new_y3;
  *x4 = new_x4;
  *y4 = new_y4;
}

void convert_coordinates3(float q, float *x1, float *y1, float *x2, float *y2, float *x3, float *y3)
{
  float new_x1 = (1 - q) * (*x1) + q * (*x2);
  float new_y1 = (1 - q) * (*y1) + q * (*y2);
  float new_x2 = (1 - q) * (*x2) + q * (*x3);
  float new_y2 = (1 - q) * (*y2) + q * (*y3);
  float new_x3 = (1 - q) * (*x3) + q * (*x1);
  float new_y3 = (1 - q) * (*y3) + q * (*y1);

  *x1 = new_x1;
  *y1 = new_y1;
  *x2 = new_x2;
  *y2 = new_y2;
  *x3 = new_x3;
  *y3 = new_y3;
}

void draw_nested_squares(SDL_Surface *s, float r, float u, float d, int n, float alpha)
{
  draw_axis(s);

  float q = 0.1;
  float x1 = - r;
  float y1 = - r;
  float x2 = - r;
  float y2 = + r;
  float x3 = + r;
  float y3 = + r;
  float x4 = + r;
  float y4 = - r;

  affine_transform(&x1, &y1, u, d, alpha);
  affine_transform(&x2, &y2, u, d, alpha);
  affine_transform(&x3, &y3, u, d, alpha);
  affine_transform(&x4, &y4, u, d, alpha);

  draw_square(s, x1 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y1,
                 x2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y2, 
                 x3 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y3,
                 x4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y4);

  for (int i = 1; i <= n; i++)
  {
    convert_coordinates4(q, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);

    draw_square(s, x1 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y1,
                   x2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y2, 
                   x3 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y3,
                   x4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y4);
  }
}

void draw_nested_triangles(SDL_Surface *s, float r, float u, float d, int n, float alpha)
{
  draw_axis(s);

  float q = 0.1;
  float x1 = -r;
  float y1 = 2 * r * sqrt(3) / 6;
  float x2 = 0;
  float y2 = -2 * r * sqrt(3) / 3;
  float x3 = r;
  float y3 = 2 * r * sqrt(3) / 6;

  affine_transform(&x1, &y1, u, d, alpha);
  affine_transform(&x2, &y2, u, d, alpha);
  affine_transform(&x3, &y3, u, d, alpha);

  draw_triangle(s, x1 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y1,
                   x2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y2, 
                   x3 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y3);

  for (int i = 1; i <= n; i++)
  {
    convert_coordinates3(q, &x1, &y1, &x2, &y2, &x3, &y3);

    draw_triangle(s, x1 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y1,
                     x2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y2, 
                     x3 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y3);
  }
}

void draw_nested_pentagons(SDL_Surface *s, float r, float u, float d, int n, float alpha)
{
  draw_axis(s);

  float q = 0.1;
  float x1 = r * sin(0);
  float y1 = r * cos(0);
  float x2 = r * sin(2 * 3.14 / 5);
  float y2 = r * cos(2 * 3.14 / 5);
  float x3 = r * sin(4 * 3.14 / 5);
  float y3 = r * cos(4 * 3.14 / 5);
  float x4 = r * sin(6 * 3.14 / 5);
  float y4 = r * cos(6 * 3.14 / 5);
  float x5 = r * sin(8 * 3.14 / 5);
  float y5 = r * cos(8 * 3.14 / 5);
  
  affine_transform(&x1, &y1, u, d, alpha);
  affine_transform(&x2, &y2, u, d, alpha);
  affine_transform(&x3, &y3, u, d, alpha);
  affine_transform(&x4, &y4, u, d, alpha);
  affine_transform(&x5, &y5, u, d, alpha);

  draw_pentagon(s, x1 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y1,
                   x2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y2, 
                   x3 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y3,
                   x4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y4,
                   x5 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y5);

  for (int i = 1; i <= n; i++)
  {
    convert_coordinates5(q, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4, &x5, &y5);

    draw_pentagon(s, x1 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y1,
                     x2 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y2, 
                     x3 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y3,
                     x4 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y4,
                     x5 + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y5);
  }
}
