#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *to_base64(const unsigned char *input, size_t length) {
    static const char encoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    uint8_t buffer[3] = { 0 };
    uint8_t outbuf[4] = { 0 };
    size_t i, j, padding;
    int n;
    char *output;

    if (length == 0) return NULL;

    padding = length % 3; // Number of '=' to append
    output = malloc(((length + 2) / 3) * 4 + 1);
    if (!output) return NULL;

    for (i = j = n = 0; i < length;) {
        buffer[n++] = input[i++];
        if (n == 3 || i == length) {
            outbuf[0] = (buffer[0] & 0xFC) >> 2;
            outbuf[1] = ((buffer[0] & 0x03) << 4) | ((buffer[1] & 0xF0) >> 4);
            outbuf[2] = ((buffer[1] & 0x0F) << 2) | ((buffer[2] & 0xC0) >> 6);
            outbuf[3] = buffer[2] & 0x3F;

            if (i - n == 1) {
                outbuf[2] = 0x40; // '=' in encoding table
            }
            if (i - n <= 2) {
                outbuf[3] = 0x40; // '=' in encoding table
            }

            output[j++] = encoding[outbuf[0]];
            output[j++] = encoding[outbuf[1]];
            output[j++] = encoding[outbuf[2]];
            output[j++] = encoding[outbuf[3]];

            n = 0;
        }
    }

    while (j < ((length + 2) / 3) * 4) {
        output[j++] = '=';
    }
    output[j] = '\0';

    return output;
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(length);
    if (fread(buffer, 1, length, file) != length) {
        perror("Failed to read file");
        fclose(file);
        free(buffer);
        exit(1);
    }

    fclose(file);

    char *base64_data = to_base64(buffer, length);
    printf("Image Name: %s\nBase64 String: %s\n", filename, base64_data);

    free(buffer);
    free(base64_data);
}