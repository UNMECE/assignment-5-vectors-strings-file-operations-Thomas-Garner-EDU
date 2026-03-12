#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pixel.h" 

void load_pixel(std::string filename, std::vector<Pixel>& pixel_list) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        Pixel p;
        size_t first_index = 0;
        size_t second_index = line.find(',');

        p.x = std::stoi(line.substr(first_index, second_index - first_index));
        first_index = second_index + 1;
        second_index = line.find(',', first_index);

        p.y = std::stoi(line.substr(first_index, second_index - first_index));
        first_index = second_index + 1;
        second_index = line.find(',', first_index);

        p.r = std::stof(line.substr(first_index, second_index - first_index));
        first_index = second_index + 1;
        second_index = line.find(',', first_index);

        p.g = std::stof(line.substr(first_index, second_index - first_index));
        first_index = second_index + 1;

        p.b = std::stof(line.substr(first_index));

        pixel_list.push_back(p);
    }
    infile.close();
}

void average_colors(std::vector<Pixel>& pixel_list) {
    if (pixel_list.empty()) {
        std::cout << "No pixels to average." << std::endl;
        return;
    }

    double sum_r = 0.0;
    double sum_g = 0.0;
    double sum_b = 0.0;

    for (size_t i = 0; i < pixel_list.size(); i++) {
        sum_r += pixel_list[i].r;
        sum_g += pixel_list[i].g;
        sum_b += pixel_list[i].b;
    }

    std::cout << "Average R: " << (sum_r / pixel_list.size()) << std::endl;
    std::cout << "Average G: " << (sum_g / pixel_list.size()) << std::endl;
    std::cout << "Average B: " << (sum_b / pixel_list.size()) << std::endl;
}

void flip_vertically(std::vector<Pixel>& pixel_list) {
    int y_max = 255;
    for (size_t i = 0; i < pixel_list.size(); i++) {
        pixel_list[i].y = y_max - pixel_list[i].y;
    }
}

void save_flipped(std::string filename, std::vector<Pixel>& pixel_list) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not create output file." << std::endl;
        return;
    }

    for (size_t i = 0; i < pixel_list.size(); i++) {
        outfile << pixel_list[i].x << ","
                << pixel_list[i].y << ","
                << pixel_list[i].r << ","
                << pixel_list[i].g << ","
                << pixel_list[i].b << "\n";
    }
    outfile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string input_filename = argv[1];
    std::vector<Pixel> pixel_list;

    std::cout << "Loading pixels from " << input_filename << "..." << std::endl;
    load_pixel(input_filename, pixel_list);

    if (pixel_list.empty()) {
        std::cerr << "Failed to load data or file was empty. Exiting." << std::endl;
        return 1;
    }

    average_colors(pixel_list);

    flip_vertically(pixel_list);

    save_flipped("flipped.dat", pixel_list);


    return 0;
}
