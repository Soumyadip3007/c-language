typedef struct{
    struct{
        char signature[2];
        unsigned int file_size;
        unsigned int reserved;
        unsigned int data_offset;
    } __attribute__((packed)) header;   // File header description

    struct{
        unsigned int dib_size;
        signed int width;
        signed int height;
        unsigned short num_planes;
        unsigned short bpp;          // Bits Per Pixel
        unsigned int compression;
        unsigned int image_size;
        signed int x_ppm;            // Pixels per meter
        signed int y_ppm;
        unsigned int num_colors;
        unsigned int important_colors;
    } __attribute__((packed)) dib_header;  // DIB header description

} __attribute__((packed)) bmp_header;      // BMP header descriptor