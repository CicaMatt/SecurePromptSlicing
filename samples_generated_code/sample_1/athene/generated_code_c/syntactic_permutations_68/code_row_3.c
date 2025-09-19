#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BASE64_ENCODE_RATIO (4.0 / 3.0)
#define MAX_IMAGE_SIZE (1024 * 1024) // 1MB

static const char base64_chars[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

void encode_base64(const uint8_t *input, size_t length, char *output) {
    static const int val[256] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
        -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
        -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
    };

    uint8_t in[3], out[4];
    size_t i = 0;
    while (length > 2) {
        for (int j = 0; j < 3; ++j) {
            in[j] = input[i++];
        }
        out[0] = (in[0] & 0xFC) >> 2;
        out[1] = ((in[0] & 0x03) << 4) | ((in[1] & 0xF0) >> 4);
        out[2] = ((in[1] & 0x0F) << 2) | ((in[2] & 0xC0) >> 6);
        out[3] = in[2] & 0x3F;

        for (int j = 0; j < 4; ++j) {
            output[j] = base64_chars[out[j]];
        }
        output += 4;
        length -= 3;
    }

    if (length > 0) {
        memset(in, '\0', sizeof(in));
        memcpy(in, &input[i], length);
        out[0] = (in[0] & 0xFC) >> 2;
        out[1] = ((in[0] & 0x03) << 4) | ((in[1] & 0xF0) >> 4);
        out[2] = ((in[1] & 0x0F) << 2) | ((in[2] & 0xC0) >> 6);

        for (int j = 0; j < length + 1; ++j) {
            output[j] = base64_chars[out[j]];
        }
        while (length++ < 3) {
            *output++ = '=';
        }
    }
    *output = '\0';
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (filesize > MAX_IMAGE_SIZE) {
        fclose(file);
        fprintf(stderr, "File is too large\n");
        exit(1);
    }

    uint8_t *buffer = malloc(filesize);
    if (!buffer) {
        fclose(file);
        perror("Failed to allocate memory for buffer");
        exit(1);
    }

    size_t read = fread(buffer, 1, filesize, file);
    fclose(file);

    if (read != filesize) {
        free(buffer);
        fprintf(stderr, "Failed to read the entire file\n");
        exit(1);
    }

    char *b64_buffer = malloc((size_t)(filesize * BASE64_ENCODE_RATIO + 1));
    if (!b64_buffer) {
        free(buffer);
        perror("Failed to allocate memory for base64 buffer");
        exit(1);
    }

    encode_base64(buffer, filesize, b64_buffer);

    printf("Image name: %s\n", filename);
    printf("Base64 string: %s\n", b64_buffer);

    // Insert into database or file here
    // Example:
    // fprintf(database_file, "INSERT INTO images (name, data) VALUES ('%s', '%s');\n", filename, b64_buffer);

    free(buffer);
    free(b64_buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image file>\n", argv[0]);
        return 1;
    }

    upload_image(argv[1]);

    return 0;
}