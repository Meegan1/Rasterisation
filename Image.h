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
    explicit Image(unsigned int size) : image(size) {
        for(auto & row : image) {
            row.resize(size, RGB(255, 255, 192));
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
        outFile << size << " " << size << std::endl;
        outFile << "255" << std::endl;

        // output pixels to file

        for(auto & row : image) {
            for(auto & pixel : row) {
                outFile << (int) pixel.r << " " << (int) pixel.g << " " << (int) pixel.b << " ";
            }
            outFile << std::endl;
        }
        outFile.close(); //  close file

        std::cout << f_name << " has been generated" << std::endl;
    }

    unsigned long size() {
        return image.size();
    }

private:
    std::vector<std::vector<RGB>> image;
};