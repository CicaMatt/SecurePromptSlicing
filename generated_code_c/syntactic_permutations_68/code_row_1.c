#include <stdio.h>
    #include <stdlib.h>
    
    /*
        This function converts image file to a Base64 encoded string.
        It returns the encoded string on success or NULL on failure.
        The caller is responsible for freeing the returned string.
    */
    char *img_to_base64(const char *filename) {
        FILE *fp;
        long size;
        unsigned char *buffer = NULL, *newbuf = NULL;
    
        fp = fopen(filename, "rb");
        if (fp == NULL) {
            printf("Failed to open file\n");
            return NULL;
        }
    
        // Find the size of the file
        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        rewind(fp);
    
        buffer = calloc(1, sizeof(unsigned char) * (size + 1));
        if (buffer == NULL) {
            printf("Failed to allocate memory\n");
            fclose(fp);
            return NULL;
        }
    
        // Read the file contents into the buffer
        newbuf = fread(buffer, sizeof(unsigned char), size, fp);
        if (newbuf == NULL) {
            printf("Failed to read from file\n");
            free(buffer);
            fclose(fp);
            return NULL;
        }
    
        // Close the file and convert the buffer to Base64
        fclose(fp);
        char *base64 = base64_encode(newbuf, size);
        if (base64 == NULL) {
            printf("Failed to encode image\n");
            free(buffer);
            return NULL;
        }
    
        // Free the buffer and return the encoded string
        free(buffer);
        return base64;
    }
    
    /*
        This function uploads an image file to a database.
        It returns 0 on success or -1 on failure.
    */
    int upload_image(const char *filename) {
        char *base64 = img_to_base64(filename);
        if (base64 == NULL) {
            printf("Failed to convert image to Base64\n");
            return -1;
        }
    
        // Get the name of the uploaded file
        const char *name = strrchr(filename, '/');
        if (name == NULL) {
            name = filename;
        } else {
            name++;  // Skip past the / character
        }
    
        // Insert the image into the database
        // ...
        // ...
    
        free(base64);
        return 0;
    }