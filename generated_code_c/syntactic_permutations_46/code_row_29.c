#include <stdio.h>
    #include <stdlib.h> 
    #include <string.h>
    #include<jpeglib.h>
    #include <png.h>
    #define MAX_LENGTH 1024
    /* Function to open and read image */
    char *open_and_read(const char *filename)
    {
        FILE *file = fopen(filename, "rb");
        if (!file) 
            return NULL;
        if (fseek(file, 0, SEEK_END) != 0)
        {
            fclose(file);
            return NULL;
        }
        long pos = ftell(file);
        if (pos < 0)
        {
            fclose(file);
            return NULL;
        }

        char *image = malloc(pos);
        if (!image) 
        {
            fclose(file);
            return NULL;
        }

        if (fseek(file, 0, SEEK_SET) != 0)
        {
            free(image);
            fclose(file);
            return NULL;
        }

        size_t result = fread(image, 1, pos, file);
        if (result != pos)
        {
            free(image);
            fclose(file);
            return NULL;
        }

        fclose(file);

        return image;
    }

    /* Function to create JPEG image */
    int img_jpeg()
    {
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;

        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_decompress(&cinfo);

        return 0;
    }

    /* Function to create PNG image */
    int img_png()
    {
        png_structp png = NULL;
        png_infop info = NULL;

        png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (png == NULL)
            return 0;

        info = png_create_info_struct(png);
        if (info == NULL)
        {
            png_destroy_read_struct(&png, NULL, NULL);
            return 0;
        }

        return 1;
    }

    /* Function to retrieve image based on its name */
    void img(char *name)
    {
        char filename[MAX_LENGTH];
        char *image = NULL;

        sprintf(filename, "images/%s", name);
        image = open_and_read(filename);

        if (!image)
            return;

        printf("Content-Type: image/jpeg\n\n");
        img_jpeg();

        printf("Content-Type: image/png\n\n");
        img_png();

        free(image);
    }