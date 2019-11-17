#include <iostream>
#include <fstream>
#include <numeric>
#include "Image.h"
#include "Triangle.h"
#include "Texture.h"

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

    for (unsigned long x = 0; x < image.get_width(); x++) {
        for (unsigned long y = 0; y < image.get_height(); y++) {
            float alpha;
            float beta;
            float gamma;
            get_barycentric(Point(x, y), triangle.A.position, triangle.B.position, triangle.C.position, alpha, beta, gamma);

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

void half_plane() {
    Image image(128);
    Triangle triangle(
            Vertex(61, 10, RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(100, 100, RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(25, 90, RGB(0, 0, 255), UV(0.230169, 0.222781))
    );

    for (unsigned long x = 0; x < image.get_width(); x++) {
        for (unsigned long y = 0; y < image.get_height(); y++) {
            float alpha;
            float beta;
            float gamma;
            get_barycentric(Point(x, y), triangle.A.position, triangle.B.position, triangle.C.position, alpha, beta, gamma);


            image[x][y].r = (alpha < 0.0) ? 0 : 255;
            image[x][y].g = (beta < 0.0) ? 0 : 255;
            image[x][y].b = (gamma < 0.0) ? 0 : 255;
        }
    }

    image.toFile("halfplane");
}

void triangle() {
    Image image(128);
    Triangle triangle(
            Vertex(61, 10, RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(100, 100, RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(25, 90, RGB(0, 0, 255), UV(0.230169, 0.222781))
    );

    for (unsigned long x = 0; x < image.get_width(); x++) {
        for (unsigned long y = 0; y < image.get_height(); y++) {
            float alpha;
            float beta;
            float gamma;
            get_barycentric(Point(x, y), triangle.A.position, triangle.B.position, triangle.C.position, alpha, beta, gamma);


            if ((alpha < 0.0) || (beta < 0.0) || (gamma < 0.0))
                continue;

            image[x][y].r = 0;
            image[x][y].g = 0;
            image[x][y].b = 0;
        }
    }

    image.toFile("triangle");
}

void rgb() {
    Image image(128);
    Triangle triangle(
            Vertex(61, 10, RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(100, 100, RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(25, 90, RGB(0, 0, 255), UV(0.230169, 0.222781))
    );

    for (unsigned long x = 0; x < image.get_width(); x++) {
        for (unsigned long y = 0; y < image.get_height(); y++) {
            float alpha;
            float beta;
            float gamma;
            get_barycentric(Point(x, y), triangle.A.position, triangle.B.position, triangle.C.position, alpha, beta, gamma);

            if ((alpha < 0.0) || (beta < 0.0) || (gamma < 0.0))
                continue;

            Color color_r = clamp((alpha * triangle.A.color.r) + (beta * triangle.B.color.r)
                                  + (gamma * triangle.C.color.r));
            Color color_g = clamp((alpha * triangle.A.color.g) + (beta * triangle.B.color.g)
                                  + (gamma * triangle.C.color.g));
            Color color_b = clamp((alpha * triangle.A.color.b) + beta * (triangle.B.color.b)
                                  + (gamma * triangle.C.color.b));

            image[x][y].r = color_r;
            image[x][y].g = color_g;
            image[x][y].b = color_b;
        }
    }

    image.toFile("rgb");
}

RGB BilinearLookup(Texture& tex, float s, float t)
{ // BilinearLookup()
    int i = s;                    // truncates s to get i
    int j = t;                    // truncates t to get j
    float sParm = s - i;          // compute s for interpolation
    float tParm = t - j;          // compute t for interpolation

    // grab four nearest texel colours
    RGB colour00 = tex[i][j];
    RGB colour01 = tex[i][j + 1];
    RGB colour10 = tex[i + 1][j];
    RGB colour11 = tex[i + 1][j + 1];

    // compute colours on edges
    RGB colour0;

    colour0.r = colour00.r + tParm * (colour01.r - colour00.r);
    colour0.g = colour00.g + tParm * (colour01.g - colour00.g);
    colour0.b = colour00.b + tParm * (colour01.b - colour00.b);

    RGB colour1;
    colour1.r = colour10.r + tParm * (colour11.r - colour10.r);
    colour1.g = colour10.g + tParm * (colour11.g - colour10.g);
    colour1.b = colour10.b + tParm * (colour11.b - colour10.b);

    // compute colour for interpolated texel
    RGB colour3;
    colour3.r = colour1.r + sParm * (colour1.r - colour0.r);
    colour3.g = colour1.g + sParm * (colour1.g - colour0.g);
    colour3.b = colour1.b + sParm * (colour1.b - colour0.b);

    return colour3;
} // BilinearLookup()

void texture() {
    Texture texture("earth.ppm");

    Image image(128);
    Triangle triangle(
            Vertex(61, 10, RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(100, 100, RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(25, 90, RGB(0, 0, 255), UV(0.230169, 0.222781))
    );

    for (unsigned long x = 0; x < image.get_width(); x++) {
        for (unsigned long y = 0; y < image.get_height(); y++) {
            float alpha;
            float beta;
            float gamma;
            get_barycentric(Point(x, y), triangle.A.position, triangle.B.position, triangle.C.position, alpha, beta, gamma);

            if ((alpha < 0.0) || (beta < 0.0) || (gamma < 0.0))
                continue;

            float s = (alpha * (triangle.A.uv.u * texture->get_width()))
                      + (beta * (triangle.B.uv.u * texture->get_width()))
                      + (gamma * (triangle.C.uv.u * texture->get_width()));

            float t = texture->get_height() - ((alpha * (triangle.A.uv.v * texture->get_height()))
                      + (beta * (triangle.B.uv.v * texture->get_height()))
                      + (gamma * (triangle.C.uv.v * texture->get_height())));

//            RGB color =  texture[s][t];
            RGB color = BilinearLookup(texture, s, t);

            image[x][y].r = color.r;
            image[x][y].g = color.g;
            image[x][y].b = color.b;
        }
    }

    for (unsigned long x = 0; x < image.get_width(); x++) {
        for (unsigned long y = 0; y < image.get_height(); y++) {
            float alpha;
            float beta;
            float gamma;
            get_barycentric(Point(x, y), triangle.A.position, triangle.B.position, triangle.C.position, alpha, beta, gamma);

            if ((alpha < 0.0) || (beta < 0.0) || (gamma < 0.0))
                continue;

            float s = (alpha * (triangle.A.uv.u * texture->get_width()))
                      + (beta * (triangle.B.uv.u * texture->get_width()))
                      + (gamma * (triangle.C.uv.u * texture->get_width()));

            float t = texture->get_height() - ((alpha * (triangle.A.uv.v * texture->get_height()))
                                               + (beta * (triangle.B.uv.v * texture->get_height()))
                                               + (gamma * (triangle.C.uv.v * texture->get_height())));

            RGB color =  texture[s][t];

            texture[s][t].r = 255;
            texture[s][t].g = 0;
            texture[s][t].b = 0;
        }
    }
    texture->toFile("earth_with_chunk");
    image.toFile("texture");
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    abg();
    half_plane();
    triangle();
    rgb();
    texture();
    return 0;
}