//
// Created by Jake Meegan on 17/11/2019.
//

#include "Render.h"
#include "Triangle.h"

void Render::abg() {
    Image image(128); // create canvas
    Triangle triangle(
            Vertex(61, 10, RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(100, 100, RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(25, 90, RGB(0, 0, 255), UV(0.230169, 0.222781))
    ); // create triangle with attributes

    // loop through every pixel
    for (unsigned long y = image.get_height() - 1; y != -1; y--) {
        for (unsigned long x = 0; x < image.get_width(); x++) {
            float alpha, beta, gamma;
            triangle.get_barycentric(Point(x, y), alpha, beta, gamma); // get barycentric coords

            // get colours and clamp between 0-255
            Color color_r = clamp(100 + (100 * alpha));
            Color color_g = clamp(100 + (100 * beta));
            Color color_b = clamp(100 + (100 * gamma));

            // set pixel to correct colours
            image[x][y].r = color_r;
            image[x][y].g = color_g;
            image[x][y].b = color_b;
        }
    }

    image.toFile("abg"); // output to file
}

void Render::half_plane() {
    Image image(128); // create canvas
    Triangle triangle(
            Vertex(61, 10, RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(100, 100, RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(25, 90, RGB(0, 0, 255), UV(0.230169, 0.222781))
    ); // create triangle with attributes

    // loop through every pixel
    for (unsigned long y = image.get_height() - 1; y != -1; y--) {
        for (unsigned long x = 0; x < image.get_width(); x++) {
            float alpha, beta, gamma;
            triangle.get_barycentric(Point(x, y), alpha, beta, gamma); // get barycentric coords

            // set (r|g|b) to 0 if (alpha|beta|gamma) is less than 0, otherwise set to 255
            image[x][y].r = (alpha < 0.0) ? 0 : 255;
            image[x][y].g = (beta < 0.0) ? 0 : 255;
            image[x][y].b = (gamma < 0.0) ? 0 : 255;
        }
    }

    image.toFile("halfplane"); // output to file
}

void Render::triangle() {
    Image image(128); // create canvas
    Triangle triangle(
            Vertex(61, 10, RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(100, 100, RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(25, 90, RGB(0, 0, 255), UV(0.230169, 0.222781))
    ); // create triangle with attributes

    // loop through every pixel
    for (unsigned long y = image.get_height() - 1; y != -1; y--) {
        for (unsigned long x = 0; x < image.get_width(); x++) {
            float alpha, beta, gamma;
            triangle.get_barycentric(Point(x, y), alpha, beta, gamma); // get barycentric coords

            // skip if not in triangle
            if ((alpha < 0.0) || (beta < 0.0) || (gamma < 0.0))
                continue;

            // set colour to black
            image[x][y].r = 0;
            image[x][y].g = 0;
            image[x][y].b = 0;
        }
    }

    image.toFile("triangle"); // output to file
}

void Render::rgb() {
    Image image(128); // create canvas
    Triangle triangle(
            Vertex(61, 10, RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(100, 100, RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(25, 90, RGB(0, 0, 255), UV(0.230169, 0.222781))
    ); // create triangle with attributes

    // loop through every pixel
    for (unsigned long y = image.get_height() - 1; y != -1; y--) {
        for (unsigned long x = 0; x < image.get_width(); x++) {
            float alpha, beta, gamma;
            triangle.get_barycentric(Point(x, y), alpha, beta, gamma); // get barycentric coords

            // skip if not in triangle
            if ((alpha < 0.0) || (beta < 0.0) || (gamma < 0.0))
                continue;

            // interpolate colours between triangle
            Color color_r = clamp((alpha * triangle.A.color.r) + (beta * triangle.B.color.r)
                                  + (gamma * triangle.C.color.r));
            Color color_g = clamp((alpha * triangle.A.color.g) + (beta * triangle.B.color.g)
                                  + (gamma * triangle.C.color.g));
            Color color_b = clamp((alpha * triangle.A.color.b) + beta * (triangle.B.color.b)
                                  + (gamma * triangle.C.color.b));

            // set pixel colour to interpolated colour
            image[x][y].r = color_r;
            image[x][y].g = color_g;
            image[x][y].b = color_b;
        }
    }

    image.toFile("rgb"); // output to file
}

void Render::texture() {
    Texture texture("earth.ppm"); // create canvas

    Image image(128);
    Triangle triangle(
            Vertex(61, 10, RGB(255, 0, 0), UV(0.160268, 0.290086)),
            Vertex(100, 100, RGB(0, 255, 0), UV(0.083611, 0.159907)),
            Vertex(25, 90, RGB(0, 0, 255), UV(0.230169, 0.222781))
    ); // create triangle with attributes

    // loop through every pixel
    for (unsigned long y = image.get_height() - 1; y != -1; y--) {
        for (unsigned long x = 0; x < image.get_width(); x++) {
            float alpha, beta, gamma;
            triangle.get_barycentric(Point(x, y), alpha, beta, gamma); // get barycentric coords

            // skip if not in triangle
            if ((alpha < 0.0) || (beta < 0.0) || (gamma < 0.0))
                continue;

            // get interpolated x coord for texture
            float i = (alpha * (triangle.A.uv.u * texture->get_width()))
                      + (beta * (triangle.B.uv.u * texture->get_width()))
                      + (gamma * (triangle.C.uv.u * texture->get_width()));

            // get interpolated y coord for texture (top->down)
            float j = texture->get_height() - ((alpha * (triangle.A.uv.v * texture->get_height()))
                                               + (beta * (triangle.B.uv.v * texture->get_height()))
                                               + (gamma * (triangle.C.uv.v * texture->get_height())));

            // get colour from interpolated x/y coords in texture
            RGB color = texture[i][j];

            // set values of colour from texture
            image[x][y].r = color.r;
            image[x][y].g = color.g;
            image[x][y].b = color.b;
        }
    }
    image.toFile("texture"); // output to file
}

/*
 * Sets min/max values of value to 0-255
 */
int Render::clamp(int value) {
    if (value > 255)
        return 255;
    else if (value < 0)
        return 0;
    else
        return value;
}