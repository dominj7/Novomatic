#include "Polygon.h"


template <size_t N>
Polygon<N>::Polygon(std::array<SDL_Vertex, N> v) {
    vertices = v;
    angle = 0.0f;
    calcCenter();
}


template <size_t N>
void Polygon<N>::move(float x, float y, ssize_t index) {
    if (index >= N and index != -1)
        return;

    switch((int)index) {
        case -1:
            for (auto &v : vertices) {
                v.position.x += x;
                v.position.y += y;
            }
            break;
        default:
            vertices[index].position.x += x;
            vertices[index].position.y += y;
            break;
    }

    calcCenter();
}


template <size_t N>
void Polygon<N>::rotate(bool right) {
    float a = (right) ? 5 : -5;
    angle += a;
    float angleRad{angle * degreeToRadian};

    for (auto &v : vertices) {
        float xPrim{(v.position.x - center.x) * cos(angleRad) - (v.position.y - center.y) * sin(angleRad) + center.x};
        float yPrim{(v.position.x - center.x) * sin(angleRad) + (v.position.y - center.y) * cos(angleRad) + center.y};
        v.position.x = xPrim;
        v.position.y = yPrim;
    }

    angle = 0.0f;
}


template <size_t N>
void Polygon<N>::setColor(SDL_Color c) {
    for (auto &v : vertices)
        v.color = c;
}


template <size_t N>
void Polygon<N>::draw(SDL_Renderer* renderer) {
    SDL_RenderGeometry(renderer, nullptr, vertices.begin(), N, nullptr, 0);
}


template <size_t N>
std::array<SDL_Vertex, N> Polygon<N>::getVertices() const {
    return vertices;
}


template <size_t N>
bool Polygon<N>::isColliding(const Polygon *p) const {
    return isOverlap(this, p) and isOverlap(p, this);
}


template <size_t N>
bool Polygon<N>::isOverlap(const Polygon *p1, const Polygon *p2) const {
    for (int i = 0; i < p1->getVertices().size(); ++i) {
        // perpendicular vector
        float perpX = (p1->getVertices()[i].position.y - p1->getVertices()[(i + 1) % p1->getVertices().size()].position.y) * -1;
        float perpY = p1->getVertices()[i].position.x - p1->getVertices()[(i + 1) % p1->getVertices().size()].position.x;
    
        // dot product
        float p1Min{INFINITY}, p1Max{-INFINITY};
        p1->dotProduct(perpX, perpY, &p1Min, &p1Max);
        float p2Min{INFINITY}, p2Max{-INFINITY};
        p2->dotProduct(perpX, perpY, &p2Min, &p2Max);


        // not overlap
        if (!(p1Min < p2Max and p1Max > p2Min))
            return false;
    }
    
    return true;
}


template <size_t N>
void Polygon<N>::dotProduct(float perpX, float perpY, float *_min, float *_max) const {
    for (auto v : vertices) {
        float result{v.position.x * perpX + v.position.y * perpY};
        *_min = std::min(*_min, result);
        *_max = std::max(*_max, result);
    }
}


template <size_t N>
void Polygon<N>::calcCenter() {
    center.x = 0;
    center.y = 0;

    for (auto v : vertices) {
        center.x += v.position.x;
        center.y += v.position.y;
    }

    center.x /= N;
    center.y /= N;
}


// explicit instantiation
template class Polygon<3>;
