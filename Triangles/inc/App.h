#define WIDTH 1280
#define HEIGHT 720
#define FPS 60
#include "Polygon.h"
#include "PressedKey.h"
#include <iostream>

using namespace std;


class App {
private:
    // SDL
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Const
    const SDL_Color blue;
    const SDL_Color green;
    const SDL_Color red;
    const int millisecondsPerFrame;

    // Triangles
    Polygon<3> *triangleA;
    Polygon<3> *triangleB;

    // Inputs
    array<bool, (int)PressedKey::COUNT> pressedKeyArray;
    bool appIsRunning;

public:
    App();
    ~App();
    void run();

private:
    // Init
    void initSDL();
    void initTriangles();
    void initInputs();

    // Rest
    void updateInputs();
    void updateTriangles();
    void drawTriangles();

};
