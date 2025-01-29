#include "bmp.h"
#include <stdio.h>

#define SQUARE_SIZE 24
#define BPP 24  // 24-bit BMP (8 bits per channel)
#define PADDING ((4 - (SQUARE_SIZE * 3) % 4) % 4)  // BMP row padding

typedef struct {
    bmp_header file_header;
    unsigned char pixel_data[SQUARE_SIZE][SQUARE_SIZE][3];  // 24-bit RGB pixel data
} image;

int main() {
    image o_file;

    o_file.file_header.header.signature[0] = 'B';
    o_file.file_header.header.signature[1] = 'M';
    o_file.file_header.header.file_size = sizeof(bmp_header) + (SQUARE_SIZE * 3 + PADDING) * SQUARE_SIZE;
    o_file.file_header.header.reserved = 0;
    o_file.file_header.header.data_offset = sizeof(bmp_header);

    o_file.file_header.dib_header.dib_size = sizeof(o_file.file_header.dib_header);
    o_file.file_header.dib_header.width = SQUARE_SIZE;
    o_file.file_header.dib_header.height = SQUARE_SIZE;
    o_file.file_header.dib_header.num_planes = 1;
    o_file.file_header.dib_header.bpp = BPP;
    o_file.file_header.dib_header.compression = 0;
    o_file.file_header.dib_header.image_size = (SQUARE_SIZE * 3 + PADDING) * SQUARE_SIZE;
    o_file.file_header.dib_header.x_ppm = 0;
    o_file.file_header.dib_header.y_ppm = 0;
    o_file.file_header.dib_header.num_colors = 0;
    o_file.file_header.dib_header.important_colors = 0;

    for (int x = 0; x < SQUARE_SIZE; x++) {
        for (int y = 0; y < SQUARE_SIZE; y++) {
            o_file.pixel_data[x][y][0] = 255;
            o_file.pixel_data[x][y][1] = 255;
            o_file.pixel_data[x][y][2] = 0;
        }
    }

    FILE *file = fopen("output.bmp", "wb");
    if (!file) {
        perror("Failed to create file");
        return 1;
    }

    fwrite(&o_file.file_header, sizeof(bmp_header), 1, file);

    unsigned char padding[3] = {0, 0, 0};
    for (int i = 0; i < SQUARE_SIZE; i++) {
        fwrite(o_file.pixel_data[i], 3, SQUARE_SIZE, file);
        fwrite(padding, 1, PADDING, file);
    }

    fclose(file);
    return 0;
}