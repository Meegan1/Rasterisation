//
// Created by Jake Meegan on 16/11/2019.
//

#ifndef ASSIGNMENT_3_TRIANGLE_H
#define ASSIGNMENT_3_TRIANGLE_H

float dot_product(Vector v1, Vector v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

void get_barycentric(Point p, Point a, Point b, Point c, float &alpha, float &beta, float &gamma) {
    float den = ((b.y - c.y)*(a.x - c.x)) + ((c.x - b.x) * (a.y - c.y));

    alpha = (((b.y - c.y)*(p.x - c.x)) + ((c.x - b.x) * (p.y - c.y))) / den;
    beta = (((c.y - a.y) * (p.x - c.x)) + ((a.x - c.x) * (p.y - c.y))) / den;
    gamma = 1.0f - alpha - beta;
//    Vector v0 = b - a, v1 = c - a, v2 = p - a;
//    float d00 = dot_product(v0, v0);
//    float d01 = dot_product(v0, v1);
//    float d11 = dot_product(v1, v1);
//    float d20 = dot_product(v2, v0);
//    float d21 = dot_product(v2, v1);
//
//    float invDenom = 1.0 / (d00 * d11 - d01 * d01);
//
//    beta = (d11 * d20 - d01 * d21) * invDenom;
//    gamma = (d00 * d21 - d01 * d20) * invDenom;
//    alpha = 1.0f - beta - gamma;
}

struct Triangle {
    Vertex A, B, C;
    Triangle(Vertex A, Vertex B, Vertex C) : A(A), B(B), C(C) {}
};


#endif //ASSIGNMENT_3_TRIANGLE_H
