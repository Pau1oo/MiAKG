#include "draw.h"

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cassert>

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

      float r = 100;
      int n = 10;
      float u = 0;
      float d = 0;
      float alpha = 0;
      int mouse_x = NULL;
      int mouse_y = NULL;
      int num_vertex = 3;
      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (SDL_QUIT == e.type) {
            quit = true;
          }
          if (SDL_KEYDOWN == e.type) {
            switch (e.key.keysym.scancode) {
            case SDL_SCANCODE_Q:
              alpha += 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_E:
              alpha -= 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_UP:
              d -= 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_DOWN:
              d += 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_LEFT:
              u -= 3;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              break;
            case SDL_SCANCODE_RIGHT:
              u += 3;
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
              case SDL_SCANCODE_W:
              n += 1;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              printf("%d\n", n);
              break;
            case SDL_SCANCODE_S:
              if (n == 0)
                continue;
              else
              {
                n -= 1;
                SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
                printf("%d\n", n);
              }
              break;
              case SDL_SCANCODE_1:
              if (num_vertex <= 3)
                continue;
              else
              {
                num_vertex -= 1;
                SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
              }
              break;
              case SDL_SCANCODE_2:
              num_vertex += 1;
              SDL_FillRect(loadedSurface, NULL, 0x00FFFFFF);
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
        }
        (float)mouse_x; (float)mouse_y;

        draw_nested_figures(loadedSurface, mouse_x, mouse_y, num_vertex, r, u, d, n, alpha * M_PI / 180);

        SDL_UpdateTexture(gTexture, NULL, loadedSurface->pixels, loadedSurface->pitch);
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
        SDL_RenderPresent(gRenderer);
      }
    }
  }
  close();
  return 0;
}