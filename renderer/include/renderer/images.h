#pragma once

#include <png.h>
#include <iostream>
#include <fstream>
#include <string>

namespace simplicity {

void ReadData(png_structp png_ptr, png_bytep data, png_size_t length);

class Images {
public:
        Images ();
        ~Images();

        static char* LoadPng(const std::string& filename, int& width, int& height, int& channels);


};

} /* namespace simplicity */
