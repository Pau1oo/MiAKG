#include "draw.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define RGB32(r, g, b) static_cast<uint32_t>((((static_cast<uint32_t>(b) << 8) | g) << 8) | r)

void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  assert(NULL != surface);
  assert(x < SCREEN_WIDTH);
  assert(y < SCREEN_HEIGHT);

  Uint32 *pixels = (Uint32 *)surface->pixels;
  pixels[(y * surface->w) + x] = pixel;
}

Uint32 get_pixel32(SDL_Surface *surface, int x, int y)
{
  assert(NULL != surface);
  assert(x < SCREEN_WIDTH);
  assert(y < SCREEN_HEIGHT);

  Uint32 *pixels = (Uint32 *)surface->pixels;
  return pixels[(y * surface->w) + x];
}
int my_put_pixel(int x, int y, double alpha)
{
  x = (int)(x * cos(alpha) - y * sin(alpha));
  y = (int)(x * sin(alpha) + y * cos(alpha));
  return x, y;
}

void draw(SDL_Surface *s, int a, int u, int d, double alpha)
{
  glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);
  glm::mat4 Model = glm::translate(    glm::mat4(1.0f), glm::vec3(1.0f));
  glm::vec4 Transformed = Model * Position;

  //Оси координат
  for (int i = 0; i < SCREEN_WIDTH; i++)
    put_pixel32(s, i, SCREEN_HEIGHT / 2, RGB32(105, 105, 105));

  for (int j = 0; j < SCREEN_HEIGHT; j++)
    put_pixel32(s, SCREEN_WIDTH / 2, j, RGB32(105, 105, 105));

  for (double t = -100; t <= 100; t+=0.0001) 
  {
    if (t >= -1.43 && t <= -0.7)
      continue;

    //Координаты кривой
    int x = (int)((3 * a * t) / (1 + t * t * t)) + u;
    int y = (int)((3 * a * t * t) / (1 + t * t * t)) + d;

    x, y = my_put_pixel(x, y, alpha);

    put_pixel32(s, x + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y, RGB32(0, 0, 0));
  }

  for (double t = -2; t <= 3; t += 0.07)
  {
    // Координаты прямой
    int x = (int)(a * t - a) + u;
    int y = (int)(-a * t) + d;

    my_put_pixel(x, y, alpha);

    put_pixel32(s, x + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y, RGB32(0, 0, 255));
  }

  for (double t = 0; t <= 10; t += 0.01)
  {
    //Вершина
    int x = (int)(a/30 * cos(t) + 3*a/2) + u;
    int y = (int)(a/30 * sin(t) + 3*a/2) + d;

    my_put_pixel(x, y, alpha);

    put_pixel32(s, x + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - y, RGB32(0, 128, 0));
  }
}