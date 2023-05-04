#include "App.h"


App::App() : blue({8, 61, 119, 255}), green({38, 125, 57, 255}), red({221, 49, 46, 255}), millisecondsPerFrame(1000 / FPS) {
    initSDL();
    initTriangles();
    initInputs();
}


App::~App() {
    delete triangleA;
    delete triangleB;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void App::run() {
    appIsRunning = true;
    while (appIsRunning) {
        int ticks = SDL_GetTicks();

        updateInputs();

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        updateTriangles();
        drawTriangles();

        SDL_RenderPresent(renderer);

        int elapsedTime = SDL_GetTicks() - ticks;
        if (elapsedTime < millisecondsPerFrame)
            SDL_Delay(millisecondsPerFrame - elapsedTime);
    }
}


// Private

void App::initSDL() {
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0) {
        cout<<"SDL_CreateWindowAndRenderer() failed:\t"<<SDL_GetError();
        exit(EXIT_FAILURE);
    }
    SDL_SetWindowTitle(window, "Triangles");
}


void App::initTriangles() {
    SDL_Vertex v1{1000, 100};
    SDL_Vertex v2{1000, 600};
    SDL_Vertex v3{500, 600};
    array<SDL_Vertex, 3> vertices1({v1, v2, v3});
    triangleA = new Polygon(vertices1);
    v1 = {100, 100};
    v2 = {100, 600};
    v3 = {200, 600};
    array<SDL_Vertex, 3> vertices2({v1, v2, v3});
    triangleB = new Polygon(vertices2);
}


void App::initInputs() {
    pressedKeyArray.fill(false);
    appIsRunning = false;
}


void App::updateInputs() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            appIsRunning = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    pressedKeyArray[(int) PressedKey::RIGHT] = true;
                    break;
                case SDLK_LEFT:
                    pressedKeyArray[(int) PressedKey::LEFT] = true;
                    break;
                case SDLK_UP:
                    pressedKeyArray[(int) PressedKey::UP] = true;
                    break;
                case SDLK_DOWN:
                    pressedKeyArray[(int) PressedKey::DOWN] = true;
                    break;
                case SDLK_d:
                    pressedKeyArray[(int) PressedKey::D] = true;
                    break;
                case SDLK_a:
                    pressedKeyArray[(int) PressedKey::A] = true;
                    break;
                case SDLK_w:
                    pressedKeyArray[(int) PressedKey::W] = true;
                    break;
                case SDLK_s:
                    pressedKeyArray[(int) PressedKey::S] = true;
                    break;
                case SDLK_z:
                    pressedKeyArray[(int) PressedKey::Z] = true;
                    break;
                case SDLK_x:
                    pressedKeyArray[(int) PressedKey::X] = true;
                    break;
                case SDLK_c:
                    pressedKeyArray[(int) PressedKey::C] = true;
                    break;
                case SDLK_LCTRL:
                    pressedKeyArray[(int) PressedKey::CTRL] = true;
                    break;
                default:
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT:
                    pressedKeyArray[(int) PressedKey::RIGHT] = false;
                    break;
                case SDLK_LEFT:
                    pressedKeyArray[(int) PressedKey::LEFT] = false;
                    break;
                case SDLK_UP:
                    pressedKeyArray[(int) PressedKey::UP] = false;
                    break;
                case SDLK_DOWN:
                    pressedKeyArray[(int) PressedKey::DOWN] = false;
                    break;
                case SDLK_d:
                    pressedKeyArray[(int) PressedKey::D] = false;
                    break;
                case SDLK_a:
                    pressedKeyArray[(int) PressedKey::A] = false;
                    break;
                case SDLK_w:
                    pressedKeyArray[(int) PressedKey::W] = false;
                    break;
                case SDLK_s:
                    pressedKeyArray[(int) PressedKey::S] = false;
                    break;
                case SDLK_z:
                    pressedKeyArray[(int) PressedKey::Z] = false;
                    break;
                case SDLK_x:
                    pressedKeyArray[(int) PressedKey::X] = false;
                    break;
                case SDLK_c:
                    pressedKeyArray[(int) PressedKey::C] = false;
                    break;
                case SDLK_LCTRL:
                    pressedKeyArray[(int) PressedKey::CTRL] = false;
                    break;
                default:
                    break;
            }
        }
    }
}


void App::updateTriangles() {
    float Ax{0.0}, Ay{0.0};
    float Bx{0.0}, By{0.0};
    float velocity{10.0};
    ssize_t index{-1};
    for (int i = 0; i < (int)PressedKey::COUNT and !pressedKeyArray[(int)PressedKey::CTRL]; ++i) {
        if (pressedKeyArray[i]) {
            switch ((PressedKey)i) {
                case PressedKey::RIGHT:
                    Ax += velocity;
                    break;
                case PressedKey::D:
                    Bx += velocity;
                    break;
                case PressedKey::LEFT:
                    Ax -= velocity;
                    break;
                case PressedKey::A:
                    Bx -= velocity;
                    break;
                case PressedKey::UP:
                    Ay -= velocity;
                    break;
                case PressedKey::W:
                    By -= velocity;
                    break;
                case PressedKey::DOWN:
                    Ay += velocity;
                    break;
                case PressedKey::S:
                    By += velocity;
                    break;
                case PressedKey::Z:
                    index = 0;
                    break;
                case PressedKey::X:
                    index = 1;
                    break;
                case PressedKey::C:
                    index = 2;
                    break;
                default:
                    break;
            }
        }
    }

    triangleA->move(Ax, Ay, index);
    triangleB->move(Bx, By, index);


    if (pressedKeyArray[(int)PressedKey::CTRL]) {
        if (pressedKeyArray[(int)PressedKey::RIGHT] or pressedKeyArray[(int)PressedKey::DOWN])
            triangleA->rotate(true);
        if (pressedKeyArray[(int)PressedKey::LEFT] or pressedKeyArray[(int)PressedKey::UP])
            triangleA->rotate(false);


        if (pressedKeyArray[(int)PressedKey::D] or pressedKeyArray[(int)PressedKey::S])
            triangleB->rotate(true);

        if (pressedKeyArray[(int)PressedKey::A] or pressedKeyArray[(int)PressedKey::W])
            triangleB->rotate(false);
    }


    if (triangleA->isColliding(triangleB)) {
        triangleA->setColor(red);
        triangleB->setColor(red);
       } else {
        triangleA->setColor(blue);
        triangleB->setColor(green);
    }
}


void App::drawTriangles() {
    triangleA->draw(renderer);
    triangleB->draw(renderer);
}
