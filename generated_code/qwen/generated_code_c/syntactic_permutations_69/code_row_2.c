#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENCODED_BUFFER_SIZE 1024

// Function to encode binary data to base64
void encode_base64(const unsigned char *data, size_t input_length, char *encoded_data) {
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i = 0, j = 0;
    unsigned char triplet[3];
    while (input_length > 0) {
        for (i = 0; i < 3 && input_length--; i++) {
            triplet[i] = *(data++);
        }
        encoded_data[j++] = base64_chars[(triplet[0] & 0xfc) >> 2];
        encoded_data[j++] = base64_chars[((triplet[0] & 0x03) << 4) | ((triplet[1] & 0xf0) >> 4)];
        if (i == 1) {
            encoded_data[j++] = '=';
            encoded_data[j++] = '=';
        } else if (i == 2) {
            encoded_data[j++] = base64_chars[((triplet[1] & 0x0f) << 2) | ((triplet[2] & 0xc0) >> 6)];
            encoded_data[j++] = base64_chars[triplet[2] & 0x3f];
        }
    }
    encoded_data[j] = '\0';
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    fclose(file);

    if (bytes_read != file_size) {
        fprintf(stderr, "Failed to read the entire file\n");
        free(buffer);
        return;
    }

    char *encoded_data = (char *)malloc(ENCODED_BUFFER_SIZE);
    if (!encoded_data) {
        perror("Failed to allocate memory for encoded data");
        free(buffer);
        return;
    }

    encode_base64(buffer, bytes_read, encoded_data);

    FILE *output_file = fopen("encoded_image.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(encoded_data);
        free(buffer);
        return;
    }

    fprintf(output_file, "%s\n", encoded_data);
    fclose(output_file);

    free(encoded_data);
    free(buffer);
}

int main() {
    upload_image("example.jpg");
    return 0;
}