#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE64_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

int encode_base64(const unsigned char *data, size_t input_len, char *output) {
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
        for (; i < 3; i++)
            char_array_3[i] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (i = 0; i < (i + 1); i++)
            output[j++] = BASE64_CHARS[char_array_4[i]];

        while ((i++ < 3))
            output[j++] = '=';
    }

    return j;
}

void upload_image(const char *image_path, const char *output_file) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    size_t encoded_length = ((file_size + 2) / 3) * 4;
    char *encoded_image = (char *)malloc(encoded_length + 1); // +1 for null-terminator
    if (!encoded_image) {
        fprintf(stderr, "Memory allocation error\n");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    encode_base64(buffer, file_size, encoded_image);

    FILE *output = fopen(output_file, "w");
    if (!output) {
        perror("Error opening output file");
        free(buffer);
        free(encoded_image);
        exit(EXIT_FAILURE);
    }
    
    fprintf(output, "%s", encoded_image);
    fclose(output);

    free(buffer);
    free(encoded_image);
}

int main() {
    const char *image_path = "input.jpg";
    const char *output_file = "encoded.txt";

    upload_image(image_path, output_file);

    return 0;
}