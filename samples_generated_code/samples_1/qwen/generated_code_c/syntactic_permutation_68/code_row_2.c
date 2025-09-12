#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IMAGE_SIZE 102400

const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(const unsigned char *data, size_t input_length, char *encoded_data) {
    int value = 0, valbits = -6;
    const unsigned char *data_end = data + input_length;

    while (data <= data_end) {
        unsigned char c = (data < data_end ? *data++ : 0);

        value = (value << 8) + c;
        valbits += 8;

        while (valbits >= 0) {
            *encoded_data++ = b64chars[(value >> valbits) & 0x3F];
            valbits -= 6;
        }
    }

    if (valbits > -6) *encoded_data++ = b64chars[((value << 8) >> (valbits + 8)) & 0x3F];

    while ((valbits += 6) < 0) *encoded_data++ = '=';

    *encoded_data = 0;
}

void upload_image(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    unsigned char image_buffer[MAX_IMAGE_SIZE];
    size_t image_size = fread(image_buffer, 1, sizeof(image_buffer), file);
    fclose(file);

    if (image_size == 0) {
        fprintf(stderr, "File is empty\n");
        return;
    }

    char base64_encoded[(image_size * 4 + 2) / 3 + 1];
    base64_encode(image_buffer, image_size, base64_encoded);

    printf("Image Name: %s\n", filename);
    printf("Base64 Encoded Image: %s\n", base64_encoded);
}

int main() {
    upload_image("example.jpg");
    return 0;
}