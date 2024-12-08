#include <SDL2/SDL.h>
#include <vector>
#include <numeric>
#include <cmath>
#include <cstdlib>

struct Vector3
{
    float x, y, z;
};

struct Cube
{
    Vector3 centroid;
    Vector3 vertices[8];
    int edges[12][2];
};

struct Screen
{
    SDL_Event e;
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<SDL_FPoint> points;
};

Cube *createCube(float x, float y, float z, float side)
{
    Cube *cube = (Cube *)malloc(sizeof(Cube));
    cube->centroid = {x + (side / 2), y + (side / 2), z + (side / 2)};

    cube->vertices[0] = {x, y, z};
    cube->vertices[1] = {x + side, y, z};
    cube->vertices[2] = {x, y + side, z};
    cube->vertices[3] = {x, y, z + side};
    cube->vertices[4] = {x + side, y + side, z};
    cube->vertices[5] = {x + side, y, z + side};
    cube->vertices[6] = {x, y + side, z + side};
    cube->vertices[7] = {x + side, y + side, z + side};

    cube->edges[0][0] = 0;
    cube->edges[0][1] = 1;
    cube->edges[1][0] = 0;
    cube->edges[1][1] = 2;
    cube->edges[2][0] = 0;
    cube->edges[2][1] = 3;
    cube->edges[3][0] = 1;
    cube->edges[3][1] = 4;
    cube->edges[4][0] = 1;
    cube->edges[4][1] = 5;
    cube->edges[5][0] = 2;
    cube->edges[5][1] = 6;
    cube->edges[6][0] = 2;
    cube->edges[6][1] = 4;
    cube->edges[7][0] = 3;
    cube->edges[7][1] = 5;
    cube->edges[8][0] = 3;
    cube->edges[8][1] = 6;
    cube->edges[9][0] = 4;
    cube->edges[9][1] = 7;
    cube->edges[10][0] = 5;
    cube->edges[10][1] = 7;
    cube->edges[11][0] = 6;
    cube->edges[11][1] = 7;

    return cube;
}

Screen *createScreen()
{
    SDL_Init(SDL_INIT_VIDEO);
    Screen *screen = (Screen *)malloc(sizeof(Screen));
    screen->window = SDL_CreateWindow("Funny rotating cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
    return screen;
}

void drawPoint(Screen *screen, float x, float y)
{
    SDL_FPoint point;
    point.x = x;
    point.y = y;
    screen->points.push_back(point);
}

void drawLine(Screen *screen, float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = std::sqrt((dx * dx) + (dy * dy));
    float angle = std::atan2(dy, dx);

    for (int i = 0; i < static_cast<int>(length); i++)
    {
        drawPoint(screen, x1 + (std::cos(angle) * i), y1 + (std::sin(angle) * i));
    }
}

void drawCube(Screen *screen, Cube *cube)
{
    for (Vector3 v : cube->vertices)
    {
        drawPoint(screen, v.x, v.y);
    }

    for (int i = 0; i < 12; i++)
    {
        drawLine(
            screen,
            cube->vertices[cube->edges[i][0]].x,
            cube->vertices[cube->edges[i][0]].y,
            cube->vertices[cube->edges[i][1]].x,
            cube->vertices[cube->edges[i][1]].y //
        );
    }
}

void rotateCube(Cube *cube, float alpha, float beta, float gamma)
{
    for (Vector3 &v : cube->vertices)
    {
        v.x -= cube->centroid.x;
        v.y -= cube->centroid.y;
        v.z -= cube->centroid.z;

        v.y = ((v.y * std::cos(alpha)) - (v.z * std::sin(alpha)));
        v.z = ((v.y * std::sin(alpha)) + (v.z * std::cos(alpha)));

        v.x = ((v.x * std::cos(beta)) + (v.z * std::sin(beta)));
        v.z = (-(v.x * std::sin(beta)) + (v.z * std::cos(beta)));

        v.x = ((v.x * std::cos(gamma)) - (v.y * std::sin(gamma)));
        v.y = ((v.x * std::sin(gamma)) + (v.y * std::cos(gamma)));

        v.x += cube->centroid.x;
        v.y += cube->centroid.y;
        v.z += cube->centroid.z;
    }
}

void clear(Screen *screen)
{
    SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 255);
    SDL_RenderClear(screen->renderer);
    screen->points.clear();
}

void show(Screen *screen)
{
    SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 255);
    for (SDL_FPoint point : screen->points)
    {
        SDL_RenderDrawPointF(screen->renderer, point.x, point.y);
    }
    SDL_RenderPresent(screen->renderer);
}

void freeScreen(Screen *screen)
{
    SDL_DestroyRenderer(screen->renderer);
    SDL_DestroyWindow(screen->window);
    free(screen);
}

void handleInput(Screen *screen)
{
    while (SDL_PollEvent(&screen->e))
    {
        if (screen->e.type == SDL_QUIT)
        {
            freeScreen(screen);
            SDL_Quit();
            exit(0);
        }
    }
}

int main(int argc, char *argv[])
{
    Screen *screen = createScreen();
    Cube *cube = createCube(220, 140, 0, 200);
    while (true)
    {
        clear(screen);
        drawCube(screen, cube);
        rotateCube(cube, 0.001, 0.002, 0.003);
        show(screen);
        handleInput(screen);
        SDL_Delay(5);
    }
    return 0;
}
