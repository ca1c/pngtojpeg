#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <png.h>
#include <zlib.h>

int main(int argc, char ** argv) {
    if(argc == 3) {
        png_image image;

        memset(&image, 0, (sizeof image));
        image.version = PNG_IMAGE_VERSION;

        if(png_image_begin_read_from_file(&image, argv[1]) != 0) {
            png_bytep buffer;

            image.format = PNG_FORMAT_RGBA;

            buffer = malloc(PNG_IMAGE_SIZE(image));

            if(buffer != NULL &&
            png_image_finish_read(&image, NULL, buffer, 0, NULL) != 0) {
                if(png_image_write_to_file(&image, argv[2], 0/*convert_to_8bit*/,
                buffer, 0/*row_stride*/, NULL/*colormap*/) != 0) {
                    exit(0);
                }
            }
            else {
                if(buffer == NULL) {
                    png_image_free(&image);
                }
                else {
                    free(buffer);
                }
            }
        }
        fprintf(stderr, "pngtopng: error: %s\n", image.message);
        exit(1);
    }

    exit(2);
}