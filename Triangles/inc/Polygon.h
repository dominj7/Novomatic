#ifndef POLYGON_H
#define POLYGON_H
#include <array>
#include <cmath>
#include <SDL2/SDL.h>


template <size_t N = 3>
class Polygon {
private:
    std::array<SDL_Vertex, N> vertices;
    const float degreeToRadian{M_PI / 180};
    SDL_FPoint center;  // center of gravity
    float angle;

public:
    Polygon(std::array<SDL_Vertex, N>);
    void move(float, float, ssize_t = -1);
    void rotate(bool);
    void setColor(SDL_Color);
    void draw(SDL_Renderer*);
    std::array<SDL_Vertex, N> getVertices() const;
    bool isColliding(const Polygon*) const;

private:
    bool isOverlap(const Polygon*, const Polygon*) const;
    void dotProduct(float, float, float*, float*) const;
    void calcCenter();

};


#endif
