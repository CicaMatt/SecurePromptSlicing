#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE64_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

void encode_base64(const unsigned char *data, size_t input_len, char *output) {
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (input_len--) {
        char_array_3[i++] = *(data++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                output[j++] = BASE64_CHARS[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (int k = i; k < 3; k++)
            char_array_3[k] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (int k = 0; k < i + 1; k++)
            output[j++] = BASE64_CHARS[char_array_4[k]];

        while (i++ < 3)
            output[j++] = '=';
    }

    output[j] = '\0';
}

void upload_image(const char *filename) {
    FILE *file;
    unsigned char buffer[1024];
    size_t bytes_read;

    file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open image file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *encoded_image = malloc((4 * ((file_size + 2) / 3)) + 1);
    if (!encoded_image) {
        perror("Failed to allocate memory for base64 encoding");
        fclose(file);
        return;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file))) {
        encode_base64(buffer, bytes_read, encoded_image);
    }

    fclose(file);

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.b64", filename);
    
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(encoded_image);
        return;
    }

    fwrite(encoded_image, 1, strlen(encoded_image), output_file);
    fclose(output_file);

    printf("Image encoded and saved as %s\n", output_filename);
    free(encoded_image);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_image(argv[1]);

    return EXIT_SUCCESS;
}