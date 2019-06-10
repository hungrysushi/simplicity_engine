
#include "renderer/images.h"

namespace simplicity {

void ReadData(png_structp png_ptr, png_bytep data, png_size_t length) {

        ((std::istream*)png_get_io_ptr(png_ptr))->read((char*)data, length);
}

char* Images::LoadPng(const std::string& filename, int& width, int& height, int& channels) {

        png_bytep* row_ptrs = nullptr;
        char* data = nullptr;
        unsigned int stride;

        // open file for reading
        std::ifstream in(filename, std::ios::binary);
        if (!in.is_open()) {
                std::cout << "Could not open file." << std::endl;
                return nullptr;
        }

        // validate png header bytes
        png_byte header[8];
        in.read((char*) header, 8);

        // 0 indicates successful validation
        if (png_sig_cmp(header, 0, 8)) {
                std::cout << "PNG Header could not be validated." << std::endl;
                return nullptr;
        }

        // create the png read struct
        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!png_ptr) {
                std::cout << "Couldn't create png struct." << std::endl;
                return nullptr;
        }

        // create png info struct
        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr) {
                png_destroy_read_struct(&png_ptr, nullptr, nullptr);
                return nullptr;
        }

        // error handling
        // control jumps into this block for errors
        if (setjmp(png_jmpbuf(png_ptr))) {
                png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) 0);

                if (row_ptrs) {
                        delete[] row_ptrs;
                }

                if (data) {
                        delete[] data;
                }

                std::cout << "Error reading png file." << std::endl;
                return nullptr;
        }

        // set the read handler
        png_set_read_fn(png_ptr, (png_voidp) &in, ReadData);

        // skip header bytes when reading data
        png_set_sig_bytes(png_ptr, 8);
        png_read_info(png_ptr, info_ptr);

        png_uint_32 img_width = png_get_image_width(png_ptr, info_ptr);
        png_uint_32 img_height = png_get_image_height(png_ptr, info_ptr);
        png_uint_32 bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        png_uint_32 num_channels = png_get_channels(png_ptr, info_ptr);
        png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);

        row_ptrs = new png_bytep[img_height];
        stride = img_width * bit_depth * num_channels / 8;
        data = new char[img_height * stride];

        // set row pointers in reverse, to account for how opengl expects it
        for (size_t i = 0; i < img_height; i++) {
                png_uint_32 reversed = (img_height - i - 1) * stride;
                row_ptrs[i] = (png_bytep) data + reversed;
        }

        // read image, which should call the handler registered earlier
        png_read_image(png_ptr, row_ptrs);

        // clean up
        delete[] (png_bytep)row_ptrs;
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) 0);

        // set references and return buffer
        width = img_width;
        height = img_height;
        channels = num_channels;
        return data;
}

} /* namespace simplicity */
