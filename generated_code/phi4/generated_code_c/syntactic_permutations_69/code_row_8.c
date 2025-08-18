#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_base64(const unsigned char *input, size_t length, char *output) {
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (length--) {
        char_array_3[i++] = *(input++);
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
        for (int k = i; k < 3; k++) {
            char_array_3[k] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (int k = 0; k < i + 1; k++) {
            output[j++] = base64_chars[char_array_4[k]];
        }

        while (i++ < 3) {
            output[j++] = '=';
        }
    }

    output[j] = '\0';
}

void upload_image(const char *input_filename, const char *output_filename) {
    FILE *in_file = fopen(input_filename, "rb");
    if (!in_file) {
        perror("File opening failed");
        return;
    }

    fseek(in_file, 0, SEEK_END);
    long file_size = ftell(in_file);
    rewind(in_file);

    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    fread(buffer, 1, file_size, in_file);
    fclose(in_file);

    size_t encoded_length = 4 * ((file_size + 2) / 3);
    char *encoded_str = (char *)malloc(encoded_length + 1);

    encode_base64(buffer, file_size, encoded_str);

    FILE *out_file = fopen(output_filename, "w");
    if (!out_file) {
        perror("File opening failed");
        free(buffer);
        free(encoded_str);
        return;
    }

    fwrite(encoded_str, strlen(encoded_str), 1, out_file);
    fclose(out_file);

    free(buffer);
    free(encoded_str);
}

int main() {
    upload_image("input.jpg", "output.txt");
    return 0;
}