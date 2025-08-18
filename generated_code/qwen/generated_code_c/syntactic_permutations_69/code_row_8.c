#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_base64(const unsigned char *input, size_t length, char *output) {
    int i = 0;
    int j = 0;
    unsigned char triplet[3];
    unsigned char encoded[4];

    while (length > 0) {
        memset(triplet, 0, sizeof(triplet));
        for (i = 0; i < length && i < 3; ++i) {
            triplet[i] = input[j++];
        }

        encoded[0] = (triplet[0] & 0xfc) >> 2;
        encoded[1] = ((triplet[0] & 0x03) << 4) + ((triplet[1] & 0xf0) >> 4);
        encoded[2] = ((triplet[1] & 0x0f) << 2) + ((triplet[2] & 0xc0) >> 6);
        encoded[3] = triplet[2] & 0x3f;

        for (i = 0; i < length && i < 4; ++i) {
            output[j++] = base64_chars[encoded[i]];
        }

        if (length == 1) {
            output[j++] = '=';
            output[j++] = '=';
        } else if (length == 2) {
            output[j++] = '=';
        }

        length -= i;
    }
    output[j] = '\0';
}

void upload_image(const char *image_path, const char *output_file) {
    FILE *input_stream = fopen(image_path, "rb");
    if (!input_stream) {
        perror("Error opening file for reading");
        return;
    }

    fseek(input_stream, 0, SEEK_END);
    long image_size = ftell(input_stream);
    rewind(input_stream);

    unsigned char *image_data = (unsigned char *)malloc(image_size);
    if (!image_data) {
        fclose(input_stream);
        perror("Memory allocation failed");
        return;
    }

    fread(image_data, 1, image_size, input_stream);
    fclose(input_stream);

    size_t encoded_length = ((image_size + 2) / 3) * 4;
    char *encoded_image = (char *)malloc(encoded_length + 1);
    if (!encoded_image) {
        free(image_data);
        perror("Memory allocation failed");
        return;
    }

    encode_base64(image_data, image_size, encoded_image);

    FILE *output_stream = fopen(output_file, "wb");
    if (!output_stream) {
        free(image_data);
        free(encoded_image);
        perror("Error opening file for writing");
        return;
    }

    fwrite(encoded_image, 1, strlen(encoded_image), output_stream);
    fclose(output_stream);

    free(image_data);
    free(encoded_image);
}

int main() {
    const char *image_path = "example.jpg";
    const char *output_file = "encoded_image.txt";

    upload_image(image_path, output_file);

    return 0;
}