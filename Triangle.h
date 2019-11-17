//
// Created by Jake Meegan on 16/11/2019.
//

#ifndef ASSIGNMENT_3_TRIANGLE_H
#define ASSIGNMENT_3_TRIANGLE_H

/*
 * Struct for Triangle
 */
struct Triangle {
    Vertex A, B, C;
    Triangle(Vertex A, Vertex B, Vertex C) : A(A), B(B), C(C) {}

    // Get barycentric co-ordinates at point p, from vertices [A, B, C]
    void get_barycentric(Point p, float &alpha, float &beta, float &gamma) {
        Point a = A.position;
        Point b = B.position;
        Point c = C.position;

        float den = ((b.y - c.y)*(a.x - c.x)) + ((c.x - b.x) * (a.y - c.y));

        alpha = (((b.y - c.y)*(p.x - c.x)) + ((c.x - b.x) * (p.y - c.y))) / den;
        beta = (((c.y - a.y) * (p.x - c.x)) + ((a.x - c.x) * (p.y - c.y))) / den;
        gamma = 1.0f - alpha - beta;
    }
};


#endif //ASSIGNMENT_3_TRIANGLE_H
