#include <iostream>
#include <fstream>
#include <numeric>
#include "Image.h"
#include "Triangle.h"

//float distance(std::pair<int, int> a, std::pair<int, int> b) {
//    return std::sqrt(((a.second - a.first) * (a.second - a.first)) + ((b.second - b.first) * (b.second - b.first)));
//}


float dot_product(Vector v1, Vector v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

void get_barycentric(Point p, Point a, Point b, Point c, float &alpha, float &beta, float &gamma) {
//    float den = ((B.y - C.y)*(A.x - C.x)) + ((C.x - B.x) * (A.y - C.y));
//
//    alpha = (((B.y - C.y)*(point.x - C.x)) + ((C.x - B.x) * (point.y - C.y))) / den;
//    beta = (((C.y - A.y) * (point.x - C.x)) + ((A.x - C.x) * (point.y - C.y))) / den;
//    gamma = 1.0f - alpha - beta;
    Vector v0 = b - a, v1 = c - a, v2 = p - a;
    float d00 = dot_product(v0, v0);
    float d01 = dot_product(v0, v1);
    float d11 = dot_product(v1, v1);
    float d20 = dot_product(v2, v0);
    float d21 = dot_product(v2, v1);

    float invDenom = 1.0 / (d00 * d11 - d01 * d01);

    beta = (d11 * d20 - d01 * d21) * invDenom;
    gamma = (d00 * d21 - d01 * d20) * invDenom;
    alpha = 1.0f - beta - gamma;
}

int clamp(float value) {
    if(value > 255)
        return 255;
    else if(value < 0)
        return 0;
    else
        return value;
}

void abg() {
    Image image(128);
    Triangle triangle(
            Vertex(61, 10, RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(100, 100, RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(25, 90, RGB(0, 0, 255), UV(0.230169, 0.222781))
            );

    for (unsigned long x = 0; x < image.size(); x++) {
        for (unsigned long y = 0; y < image.size(); y++) {
            float alpha;
            float beta;
            float gamma;
            get_barycentric(Point(x, y), triangle.A.position, triangle.B.position, triangle.C.position, alpha, beta, gamma);

//
//            if ((alpha < 0.0) || (beta < 0.0) || (gamma < 0.0))
//                continue;

            Color color_r = clamp(100 + (100 * alpha));
            Color color_g = clamp(100 + (100 * beta));
            Color color_b = clamp(100 + (100 * gamma));

            image[x][y].r = color_r;
            image[x][y].g = color_g;
            image[x][y].b = color_b;
        }
    }

    image.toFile("abg");
}

//Color calculateColor(float alpha, float beta, float gamma, int a, int b, int c) {
//    return alpha * a + beta * b
//          + gamma * c;
//}

int main() {
    std::cout << "Hello, World!" << std::endl;

    abg();
    return 0;
}