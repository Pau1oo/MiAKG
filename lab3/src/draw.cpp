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

void input(int* width, int* height)
{
  system("cls");
  printf("Input width: ");
  while (!scanf_s("%d", width) || *width > SCREEN_WIDTH || *width <= 0 || getchar() != '\n')
  {
    system("cls");
    printf("Invalid input\n");
    rewind(stdin);
    printf("Input width: ");
  }
  system("cls");

  printf("Input height: ");
  while (!scanf_s("%d", height) || *height > SCREEN_HEIGHT || *height <= 0 || getchar() != '\n')
  {
    system("cls");
    printf("Invalid input\n");
    rewind(stdin);
    printf("Input height: ");
  }
  system("cls");
}

void affine_transform(struct Point* points, int num_vertex, float shift_x, float shift_y, float alpha)
{ 
  for(int i = 0; i < num_vertex; i++)
  { 
    points[i].x -= SCREEN_WIDTH / 2;
    points[i].y -= SCREEN_HEIGHT / 2;
    float rotate_x = points[i].x * cos(alpha) + points[i].y * sin(alpha);
    float rotate_y = -points[i].x * sin(alpha) + points[i].y * cos(alpha);
    points[i].x = rotate_x;
    points[i].y = rotate_y;
    points[i].x += shift_x + SCREEN_WIDTH / 2;
    points[i].y += shift_y + SCREEN_HEIGHT / 2;
  }
}

void draw_figure(SDL_Surface *s, struct Point* points, int num_vertex)
{
  for(int i = 0; i < num_vertex; i++)
  {
    for (float t = 0; t <= 1; t += 0.001)
    {
      float x = (points[(i + 1) % num_vertex].x - points[i % num_vertex].x) * t + points[i % num_vertex].x;
      float y = (points[(i + 1) % num_vertex].y - points[i % num_vertex].y) * t + points[i % num_vertex].y;
      put_pixel32(s, x, y, RGB32(0, 0, 0));
    }
  }
}

void draw_vis_line(SDL_Surface *s, struct Point* points, int num_vertex)
{
  for(int i = 0; i < num_vertex - 1; i += 2)
  {
    for (float t = 0; t <= 1; t += 0.001)
    {
      float x = (points[(i + 1)].x - points[i].x) * t + points[i].x;
      float y = (points[(i + 1)].y - points[i].y) * t + points[i].y;
      put_pixel32(s, x, y, RGB32(0, 0, 0));
    }
  }
}

void draw_invis_line(SDL_Surface *s, struct Point* points, int num_vertex)
{
  for(int i = 0; i < num_vertex - 1; i += 2)
  {
    for (float t = 0; t <= 1; t += 0.001)
    {
      float x = (points[(i + 1)].x - points[i].x) * t + points[i].x;
      float y = (points[(i + 1)].y - points[i].y) * t + points[i].y;
      put_pixel32(s, x, y, RGB32(128, 255, 0));
    }
  }
}

void initialize_points(struct Point* points, int num_vertex, int r)
{
  for(int i = 0; i < num_vertex; i++)
  {
    points[i].x = (int)(r * cos(2 * M_PI * i / num_vertex) + SCREEN_WIDTH / 2);
    points[i].y = (int)(r * sin(2 * M_PI * i / num_vertex) + SCREEN_HEIGHT / 2);
  }
}

void draw(SDL_Surface *s, int width, int height, int r, int x_square, int y_square, int x_triangle, int y_triangle, float alpha, float beta)
{
  struct Point *window_points = (struct Point*)malloc(4 * sizeof(struct Point));
  struct Point *triangle_points = (struct Point*)malloc(3 * sizeof(struct Point));
  struct Point *square_points = (struct Point*)malloc(4 * sizeof(struct Point));
  struct Point *invis_line_points = (struct Point*)malloc(100 * sizeof(struct Point));
  struct Point *vis_line_points = (struct Point*)malloc(100 * sizeof(struct Point));

  window_points[0].x = (int)((SCREEN_WIDTH / 2) - (width / 2)); window_points[0].y = (int)((SCREEN_HEIGHT / 2) - (height / 2));
  window_points[1].x = (int)((SCREEN_WIDTH / 2) + (width / 2)); window_points[1].y = (int)((SCREEN_HEIGHT / 2) - (height / 2));
  window_points[2].x = (int)((SCREEN_WIDTH / 2) + (width / 2)); window_points[2].y = (int)((SCREEN_HEIGHT / 2) + (height / 2));
  window_points[3].x = (int)((SCREEN_WIDTH / 2) - (width / 2)); window_points[3].y = (int)((SCREEN_HEIGHT / 2) + (height / 2));
  int x_min = window_points[0].x, x_max = window_points[1].x, y_max = window_points[1].y, y_min = window_points[2].y;
  int* borders = (int*)malloc(4 * sizeof(int));
  borders[0] = x_min; borders[1] = x_max; borders[2] = y_min; borders[3] = y_max;

  draw_figure(s, window_points, 4);
  initialize_points(triangle_points, 3, r);
  initialize_points(square_points, 4, r);

  affine_transform(triangle_points, 3, x_triangle, y_triangle, alpha);
  affine_transform(square_points, 4, x_square, y_square, beta);

  cohen_Sutherland(triangle_points, 3, invis_line_points, vis_line_points, borders);
  draw_vis_line(s, vis_line_points, 10);
  draw_invis_line(s, invis_line_points, 10);
  free(invis_line_points); free(vis_line_points);
  cohen_Sutherland(square_points, 4, invis_line_points, vis_line_points, borders);
  draw_vis_line(s, vis_line_points, 20);
  draw_invis_line(s, invis_line_points, 20);
}

// Функция для вычисления кода Коэна-Сазерленда для точки
void assign_code(struct Point *point, int *borders) 
{
    point->b0 = (point->x < borders[0]) ? 1 : 0;  // Лево
    point->b1 = (point->x > borders[1]) ? 1 : 0;  // Право
    point->b2 = (point->y > borders[2]) ? 1 : 0;  // Низ
    point->b3 = (point->y < borders[3]) ? 1 : 0;  // Верх
}

struct Point findIntersection(struct Point p1, struct Point p2, int *borders, int edge) {
    struct Point intersection = {0, 0, 0, 0, 0, 0};
    double slope = (p2.y - p1.y) / (double)(p2.x - p1.x);

    switch (edge) {
        case 0:  // Лево
            intersection.x = borders[0];
            intersection.y = p1.y + slope * (borders[0] - p1.x);
            break;
        case 1:  // Право
            intersection.x = borders[1];
            intersection.y = p1.y + slope * (borders[1] - p1.x);
            break;
        case 2:  // Низ
            intersection.y = borders[2];
            intersection.x = p1.x + (borders[2] - p1.y) / slope;
            break;
        case 3:  // Верх
            intersection.y = borders[3];
            intersection.x = p1.x + (borders[3] - p1.y) / slope;
            break;
    }

    assign_code(&intersection, borders);
    return intersection;
}

int check_point_location(struct Point point)
{
  if((point.b0 + point.b1+ point.b2 + point.b3) == 0)
    return 0;

  if((point.b0 + point.b1+ point.b2 + point.b3) != 0)
    return 1;
}

void cohen_Sutherland(struct Point* points, int num_vertex, struct Point* invis_line_points, struct Point* vis_line_points, int* borders) 
{
    int vis_count = 0, invis_count = 0;

    for (int i = 0; i < num_vertex; i++) 
    {
        struct Point p1 = points[i];
        struct Point p2 = points[(i + 1) % num_vertex];
        
        assign_code(&p1, borders);
        assign_code(&p2, borders);

        if ((p1.b0 | p2.b0 | p1.b1 | p2.b1 | p1.b2 | p2.b2 | p1.b3 | p2.b3) == 0) 
        {
            // Оба конца отрезка внутри окна
            vis_line_points[vis_count++] = p1;
            vis_line_points[vis_count++] = p2;
        } 
        else if ((p1.b0 & p2.b0) || (p1.b1 & p2.b1) || (p1.b2 & p2.b2) || (p1.b3 & p2.b3)) 
        {
            // Оба конца отрезка в одной области, вне окна
            invis_line_points[invis_count++] = p1;
            invis_line_points[invis_count++] = p2;
        } 
        else 
        {
            // Есть пересечения с границами окна
            struct Point intersections[7];
            int intersection_count = 0;

            // Проверяем пересечение с каждой из четырех границ
            if (p1.b0 != p2.b0) 
                intersections[intersection_count++] = findIntersection(p1, p2, borders, 0);
            if (p1.b1 != p2.b1) 
                intersections[intersection_count++] = findIntersection(p1, p2, borders, 1);
            if (p1.b2 != p2.b2) 
                intersections[intersection_count++] = findIntersection(p1, p2, borders, 2);
            if (p1.b3 != p2.b3) 
                intersections[intersection_count++] = findIntersection(p1, p2, borders, 3);

            intersections[intersection_count++] = p1;
            intersections[intersection_count++] = p2;

            // Сортировка пересечений по порядку появления вдоль отрезка
            for (int j = 1; j < intersection_count; j++) 
            {
                struct Point key = intersections[j];
                int k = j - 1;
                while (k >= 0 && (intersections[k].x > key.x || (intersections[k].x == key.x && intersections[k].y > key.y))) 
                {
                    intersections[k + 1] = intersections[k];
                    k--;
                }
                intersections[k + 1] = key;
            }

            for(int i = 0; i < intersection_count - 1; i++)
              {
                if(check_point_location(intersections[i]) | check_point_location(intersections[i + 1]))
                {
                  invis_line_points[invis_count++] = intersections[i];
                  invis_line_points[invis_count++] = intersections[i + 1];
                }
                else
                {
                  vis_line_points[vis_count++] = intersections[i];
                  vis_line_points[vis_count++] = intersections[i + 1];
                }
              }
        }
    }
}




