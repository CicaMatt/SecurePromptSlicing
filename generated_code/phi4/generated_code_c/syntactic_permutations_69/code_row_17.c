#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Base64 encoding table
static const char b64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_base64(const unsigned char *data, size_t input_length, char *output) {
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3] = {0};
    unsigned char char_array_4[4] = {0};

    while (input_length--) {
        char_array_3[i++] = *(data++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; ++i)
                output[j++] = b64_chars[char_array_4[i]];
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
            output[j++] = b64_chars[char_array_4[k]];
        while (i++ < 3)
            output[j++] = '=';
    }

    output[j] = '\0';
}

void upload_image(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fsize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, fsize, file);
    buffer[fsize] = '\0';
    fclose(file);

    char encoded[3 * ((fsize + 2) / 3) + 1];
    encode_base64(buffer, fsize, encoded);

    printf("Encoded Image: %s\n", encoded);

    free(buffer);
}

int main() {
    const char *image_path = "path_to_your_image_file.jpg";
    upload_image(image_path);
    return 0;
}