#include "draw.h"

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cassert>
#include <stdlib.h>
#include <math.h>

bool init();
void close();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;
SDL_Surface *loadedSurface = NULL;

bool init()
{
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gWindow = SDL_CreateWindow("AOKG Lab 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
      }
    }
  }
  return success;
}

void close()
{
  SDL_DestroyTexture(gTexture);
  gTexture = NULL;
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  SDL_Quit();
}

int main(int argc, char *argv[])
{
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    loadedSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
      0x00FF0000,// R
      0x0000FF00,// G
      0x000000FF,// B
      0x00000000);// alpha

    gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);

    if (NULL == gTexture) {
      printf("Failed to load media!\n");
    } else {
      bool quit = false;
      SDL_Event e;
      int width = NULL; int height = NULL;
     input(&width, &height);

      int r = 100;
      int x_triangle = 0; int y_triangle = 0;
      int x_square = 0; int y_square = 0;
      float alpha = 0;
      float beta = 0;
      int mouse_x = SCREEN_WIDTH / 2;
      int mouse_y = SCREEN_HEIGHT / 2;
      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (SDL_QUIT == e.type) {
            quit = true;
          }
          if (SDL_KEYDOWN == e.type) {
            switch (e.key.keysym.scancode) {

              //triangle
            case SDL_SCANCODE_Q:
              alpha += 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_E:
              alpha -= 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_W:
              y_triangle -= 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_S:
              y_triangle += 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_A:
              x_triangle -= 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_D:
              x_triangle += 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;

            //square
            case SDL_SCANCODE_R:
              beta += 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_Y:
              beta -= 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_T:
              y_square -= 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_G:
              y_square += 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_F:
              x_square -= 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_H:
              x_square += 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;

            case SDL_SCANCODE_KP_PLUS:
              r += 2;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_KP_MINUS:
              if (r <= 0)
                continue;
              else
              {
                r -= 2;
                SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              }
              break;
            default:
              break;
            }
          }
        }
        SDL_RenderClear(gRenderer);

        if(SDL_MOUSEBUTTONDOWN == e.type)
        {
          SDL_GetMouseState(&mouse_x, &mouse_y);
          SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
        }
        (float)mouse_x; (float)mouse_y;

        draw(loadedSurface, width, height, r, x_square, y_square, x_triangle, y_triangle, alpha * M_PI / 180, beta * M_PI / 180);

        SDL_UpdateTexture(gTexture, NULL, loadedSurface->pixels, loadedSurface->pitch);
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
        SDL_RenderPresent(gRenderer);
      }
    }
  }
  close();
  return 0;
}