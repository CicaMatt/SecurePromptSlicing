#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Base64 encoding table
static const char base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

void encode_base64(const unsigned char *data, size_t input_length,
                   char *output) {
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (input_length--) {
        char_array_3[i++] = *(data++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; ++i)
                output[j++] = base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (int k = i; k < 3; ++k)
            char_array_3[k] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (int k = 0; k < i + 1; ++k)
            output[j++] = base64_chars[char_array_4[k]];

        while (i++ < 3)
            output[j++] = '=';
    }

    output[j] = '\0';
}

void upload_image(const char *image_path, const char *output_file) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open image file");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    size_t output_length = 4 * ((file_size + 2) / 3);
    char *encoded_image = (char *)malloc(output_length + 1);
    if (!encoded_image) {
        perror("Memory allocation failed");
        free(buffer);
        return;
    }

    encode_base64(buffer, file_size, encoded_image);

    FILE *output = fopen(output_file, "w");
    if (!output) {
        perror("Failed to open output file");
        free(encoded_image);
        free(buffer);
        return;
    }

    fprintf(output, "%s", encoded_image);
    fclose(output);

    free(encoded_image);
    free(buffer);
}

int main() {
    const char *image_path = "path/to/image.jpg";
    const char *output_file = "encoded_image.txt";

    upload_image(image_path, output_file);

    return 0;
}