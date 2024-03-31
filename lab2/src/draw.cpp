
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

void affine_transform(float *x, float *y, float u, float d, float alpha)
{
  float rotate_x = (*x) * cos(alpha) + (*y) * sin(alpha);
  float rotate_y = -(*x) * sin(alpha) + (*y) * cos(alpha);
  *x = rotate_x;
  *y = rotate_y;
  *x += u;
  *y += d;
}

void draw(SDL_Surface *s, float r, float u, float d, float alpha)
{
  draw_axis(s);

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
}
