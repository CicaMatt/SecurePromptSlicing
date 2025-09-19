#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ENCODED_SIZE(src_size) ((src_size + 2 - ((src_size + 2) % 3)) / 3 * 4)

const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_base64(const unsigned char* src, size_t src_len, char* dest) {
    int i = 0;
    int j = 0;
    unsigned char b3[3];
    unsigned char b4[4];

    while (src_len--) {
        b3[i++] = *(src++);
        if (i == 3) {
            b4[0] = (b3[0] & 0xfc) >> 2;
            b4[1] = ((b3[0] & 0x03) << 4) + ((b3[1] & 0xf0) >> 4);
            b4[2] = ((b3[1] & 0x0f) << 2) + ((b3[2] & 0xc0) >> 6);
            b4[3] = b3[2] & 0x3f;

            for (i = 0; i < 4; i++) {
                dest[j++] = base64_table[b4[i]];
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) {
            b3[j] = '\0';
        }

        b4[0] = (b3[0] & 0xfc) >> 2;
        b4[1] = ((b3[0] & 0x03) << 4) + ((b3[1] & 0xf0) >> 4);
        b4[2] = ((b3[1] & 0x0f) << 2) + ((b3[2] & 0xc0) >> 6);
        b4[3] = b3[2] & 0x3f;

        for (j = 0; j < i + 1; j++) {
            dest[j] = base64_table[b4[j]];
        }

        while (i++ < 3) {
            dest[j++] = '=';
        }
    }
    dest[j] = '\0';
}

void upload_image(const char* image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(file_size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, file_size, 1, file);
    fclose(file);

    size_t encoded_size = ENCODED_SIZE(file_size);
    char* base64_string = (char*)malloc(encoded_size + 1);
    if (!base64_string) {
        perror("Memory allocation failed");
        free(buffer);
        return;
    }

    encode_base64(buffer, file_size, base64_string);

    printf("Image Name: %s\n", image_path);
    printf("Base64 String: %s\n", base64_string);

    free(base64_string);
    free(buffer);
}

int main() {
    upload_image("example.jpg");
    return 0;
}