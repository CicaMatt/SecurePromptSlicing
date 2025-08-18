#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BASE64_ENCODED_LEN(len) ((((len) + 2) / 3) * 4)

static const char base64_chars[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

void base64_encode(const unsigned char *data, size_t input_length, char **output) {
    *output = (char *)malloc(BASE64_ENCODED_LEN(input_length));
    if (*output == NULL) return;

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

            for (i = 0; i < 4; ++i) {
                (*output)[j++] = base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i != 0) {
        for (; i < 3; ++i) char_array_3[i] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (i = 0; i < 4; ++i) {
            (*output)[j++] = base64_chars[char_array_4[i]];
        }

        while ((i++ < 3)) (*output)[--j] = '=';
    }

    (*output)[j] = '\0';
}

void upload_image(const char *filename, const char *output_filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) return;

    fseek(file, 0, SEEK_END);
    long file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_length);
    fread(buffer, 1, file_length, file);
    fclose(file);

    char *encoded_data;
    base64_encode(buffer, file_length, &encoded_data);

    FILE *out_file = fopen(output_filename, "w");
    if (out_file != NULL) {
        fprintf(out_file, "%s", encoded_data);
        fclose(out_file);
    }

    free(buffer);
    free(encoded_data);
}

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    upload_image(argv[1], argv[2]);
    return 0;
}