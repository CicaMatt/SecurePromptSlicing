#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    static const char encoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    *output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(*output_length + 1);
    if (encoded_data == NULL) return NULL;
    memset(encoded_data, '=', *output_length + 1);

    size_t input_part = 0;
    uint32_t temp = 0;
    for (size_t i = 0; i < input_length;) {
        switch(input_part % 3) {
            case 0:
                temp = data[i++];
                encoded_data[(i - 1) * 4 / 3] = encoding[temp >> 2];
                break;
            case 1:
                temp |= (uint32_t)data[i++] << 8;
                encoded_data[((i - 1) - 1) * 4 / 3 + 1] = encoding[(temp >> 4) & 0x3F];
                break;
            case 2:
                temp |= (uint32_t)data[i++] << 16;
                encoded_data[((i - 1) - 1) * 4 / 3 + 2] = encoding[(temp >> 6) & 0x3F];
                encoded_data[((i - 1) - 1) * 4 / 3 + 3] = encoding[temp & 0x3F];
                break;
        }
        input_part++;
    }

    if (input_length % 3 == 1) {
        encoded_data[*output_length - 2] = '=';
        encoded_data[*output_length - 1] = '=';
    } else if (input_length % 3 == 2) {
        encoded_data[*output_length - 1] = '=';
    }

    return encoded_data;
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    fread(buffer, 1, file_size, file);
    fclose(file);

    size_t encoded_length;
    char *encoded_image = base64_encode(buffer, file_size, &encoded_length);

    FILE *output_file = fopen("encoded_image.txt", "w");
    if (output_file) {
        fwrite(encoded_image, 1, encoded_length, output_file);
        fclose(output_file);
    }

    free(buffer);
    free(encoded_image);
}

int main() {
    const char *image_filename = "example.jpg";
    upload_image(image_filename);
    return 0;
}