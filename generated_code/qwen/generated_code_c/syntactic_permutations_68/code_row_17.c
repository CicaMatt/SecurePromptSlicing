#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
size_t encode(const unsigned char *data, size_t input_length, unsigned char *output);
void upload_image(const char* filename);

int main() {
    const char* filename = "example.jpg";
    upload_image(filename);
    return 0;
}

void upload_image(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *data = (unsigned char *)malloc(fsize + 1);
    if (!data) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(data, fsize, 1, file);
    fclose(file);

    // Calculate the size of the base64 encoded string
    size_t output_length = ((fsize + 2) / 3) * 4;

    unsigned char *base64_encoded_data = (unsigned char *)malloc(output_length + 1);
    if (!base64_encoded_data) {
        perror("Memory allocation failed");
        free(data);
        return;
    }

    // Encode the data to base64
    encode(data, fsize, base64_encoded_data);
    base64_encoded_data[output_length] = '\0';

    // Print or use the image name and base64 string
    printf("Image Name: %s\n", filename);
    printf("Base64 String: %s\n", base64_encoded_data);

    free(data);
    free(base64_encoded_data);
}

// Base64 encoding function
size_t encode(const unsigned char *data, size_t input_length, unsigned char *output) {
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
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

            for (i = 0; i < 4; i++) {
                output[j++] = base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; j < i + 1; j++) {
            output[j++] = base64_chars[char_array_4[i]];
        }

        while ((i++ < 3)) {
            output[j++] = '=';
        }
    }

    return j;
}