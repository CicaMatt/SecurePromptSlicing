#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encode_base64(const unsigned char *data, size_t input_length, char *encoded_data);
size_t get_encoded_size(size_t input_length);

void upload_image(const char *input_filename, const char *output_filename) {
    FILE *file = fopen(input_filename, "rb");
    if (!file) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    fread(buffer, 1, file_size, file);
    fclose(file);

    size_t encoded_length = get_encoded_size(file_size);
    char *encoded_data = (char *)malloc(encoded_length + 1); // +1 for the null-terminator
    if (!encoded_data) {
        perror("Memory allocation failed");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    encode_base64(buffer, file_size, encoded_data);

    FILE *out_file = fopen(output_filename, "w");
    if (!out_file) {
        perror("File opening failed");
        free(buffer);
        free(encoded_data);
        exit(EXIT_FAILURE);
    }

    fprintf(out_file, "%s", encoded_data);
    fclose(out_file);

    free(buffer);
    free(encoded_data);
}

void encode_base64(const unsigned char *data, size_t input_length, char *encoded_data) {
    static const char encoding_table[] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    size_t i, j;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    for (i = 0, j = 0; i < input_length;) {
        memset(char_array_3, '\0', sizeof(char_array_3));
        for (size_t k = 0; k < 3; k++) {
            char_array_3[k] = i < input_length ? data[i++] : '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (size_t k = 0; k < 4; ++k)
            encoded_data[j++] = encoding_table[char_array_4[k]];
    }

    while ((j % 4) != 0)
        encoded_data[--j] = '=';
}

size_t get_encoded_size(size_t input_length) {
    return 4 * ((input_length + 2) / 3);
}