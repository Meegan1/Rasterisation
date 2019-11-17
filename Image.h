//
// Created by Jake Meegan on 16/11/2019.
//

#include <vector>
#include "Vertex.h"

#ifndef ASSIGNMENT_3_IMAGE_H
#define ASSIGNMENT_3_IMAGE_H

#endif //ASSIGNMENT_3_IMAGE_H

class Image {
public:
    Image() = default;

    explicit Image(unsigned int size) : image(size), width(size), height(size) {
        for(auto & row : image) {
            row.resize(size, RGB(255, 255, 192));
        }
    }


    explicit Image(unsigned int width, unsigned int height) : image(width), width(width), height(height) {
        for(auto & row : image) {
            row.resize(height, RGB(255, 255, 192));
        }
    }

    std::vector<RGB> & operator[] (int x) {
        return image[x];
    }

    void toFile(const std::string& f_name) {
        std::ofstream outFile(f_name + ".ppm", std::ofstream::out);
        unsigned long size = image.size();

        // output header to file
        outFile << "P3" << std::endl;
        outFile << "# " << f_name << std::endl;
        outFile << width << " " << height << std::endl;
        outFile << "255" << std::endl;

        // output pixels to file

        for (unsigned long y = 0; y < height; y++) {
            for (unsigned long x = 0; x < width; x++) {
                outFile << (int) image[x][height-y].r << " " << (int) image[x][height-y].g << " " << (int) image[x][height-y].b << " ";

            }
            outFile << std::endl;
        }

        outFile.close(); //  close file

        std::cout << f_name << " has been generated" << std::endl;
    }

    unsigned long get_width() {
        return width;
    }

    unsigned long get_height() {
        return height;
    }

private:
    std::vector<std::vector<RGB>> image;
    unsigned long width, height;
};