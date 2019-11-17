//
// Created by Jake Meegan on 16/11/2019.
//

#ifndef ASSIGNMENT_3_VERTEX_H
#define ASSIGNMENT_3_VERTEX_H

#endif //ASSIGNMENT_3_VERTEX_H

typedef unsigned char Color;
typedef float Position;

struct Vector {
    Position x, y;
    Vector(Position x, Position y) : x(x), y(y) {}
};

struct Point {
    Position x, y;
    Point(Position x, Position y) : x(x), y(y) {}

    Vector operator - (Point other) {
        return {other.x - x, other.y - y};
    }
};

struct RGB {
    Color r, g, b;

    RGB() = default;

    RGB(Color r, Color g, Color b) : r(r), g(g), b(b) {}
};
struct UV {
    float u, v;
    UV(float u, float v) : u(u), v(v) {}
};

struct Vertex {
    Point position;
    RGB color;
    UV uv;

    Vertex(Position x, Position y, RGB color, UV uv) : position(x, y), color(color), uv(uv) {}
};
