#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void encode_base64(const unsigned char *input, size_t length, char **output);
size_t base64_encode_len(size_t input_length);

void upload_image(const char *image_path) {
    // Open the image file for reading in binary mode
    FILE *file = fopen(image_path, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Determine the size of the file
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for reading the image data
    unsigned char *buffer = (unsigned char *)malloc(fsize);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    // Read the file into the buffer
    fread(buffer, 1, fsize, file);
    fclose(file);

    // Encode the image data to base64
    char *encoded_image = NULL;
    encode_base64(buffer, fsize, &encoded_image);

    // Write the encoded data to a new file
    FILE *output_file = fopen("encoded_image.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        free(buffer);
        free(encoded_image);
        return;
    }
    fprintf(output_file, "%s", encoded_image);

    fclose(output_file);
    free(buffer);
    free(encoded_image);
}

void encode_base64(const unsigned char *input, size_t length, char **output) {
    const char base64_chars[] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    size_t encoded_size = base64_encode_len(length);
    *output = (char *)malloc(encoded_size + 1);
    if (*output == NULL) {
        perror("Memory allocation failed");
        return;
    }

    size_t i, j;
    for (i = 0, j = 0; length--) {
        uint32_t octet_a = i < length ? input[i++] : 0;
        uint32_t octet_b = i < length ? input[i++] : 0;
        uint32_t octet_c = i < length ? input[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        (*output)[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        (*output)[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        (*output)[j++] = base64_chars[(triple >> 1 * 6) & 0x3F];
        (*output)[j++] = base64_chars[(triple >> 0 * 6) & 0x3F];
    }

    for (i = 0; i < 3 - length % 3; i++)
        (*output)[encoded_size - 1 - i] = '=';

    (*output)[encoded_size] = '\0';
}

size_t base64_encode_len(size_t input_length) {
    return ((input_length + 2) / 3 * 4);
}