#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    // Function to encode the image in base64
    void upload_image(const char *filename) {
        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Cannot open image file\n");
        }
        else {
            // Read and encode the image
            fseek(file, 0L, SEEK_END);
            long int size = ftell(file);
            rewind(file);
            unsigned char *buffer = malloc(size);
            if (fread(buffer, sizeof(unsigned char), size, file) != size) {
                printf("Error reading image data\n");
            }
            else {
                // Encode the image using base64
                int encoded_size = (int)(4 * ceil((double)size / 3)) + 1;
                char *encoded_data = malloc(encoded_size);
                if (base64_encode(buffer, size, encoded_data, encoded_size) == -1) {
                    printf("Error encoding image data\n");
                }
                else {
                    // Print the encoded image
                    printf("%s", encoded_data);
                }
            }
        }
    }

    int main(int argc, char *argv[]) {
        if (argc < 2) {
            printf("Usage: %s IMAGE_FILE\n", argv[0]);
            return -1;
        }
        upload_image(argv[1]);
        return 0;
    }