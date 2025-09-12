#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Base64 encoding table */
static const char base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

/* Function to encode a buffer using base64 */
void base64_encode(const unsigned char *data, size_t input_length, char *encoded_data) {
    if (input_length == 0) return;

    const unsigned char *currentToEncode = data;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (input_length--) {
        char_array_3[i++] = *(currentToEncode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                encoded_data[j++] = base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++) char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; j < i + 1; j++)
            encoded_data[j] = base64_chars[char_array_4[j]];

        while (i++ < 3)
            encoded_data[j++] = '=';
    }

    encoded_data[j] = '\0';
}

/* Function to read image data from a file */
unsigned char *read_image(const char *filename, size_t *length) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0L, SEEK_END);
    *length = ftell(file);
    rewind(file);

    unsigned char *data = (unsigned char *)malloc(*length);
    if (!data) {
        fclose(file);
        return NULL;
    }

    fread(data, 1, *length, file);
    fclose(file);

    return data;
}

/* Function to handle image upload */
void upload_image(const char *filename) {
    size_t length;
    unsigned char *image_data = read_image(filename, &length);
    if (!image_data) {
        fprintf(stderr, "Failed to read the image.\n");
        return;
    }

    size_t encoded_length = 4 * ((length + 2) / 3);
    char *encoded_image = (char *)malloc(encoded_length + 1);

    base64_encode(image_data, length, encoded_image);

    printf("Encoded Image:\n%s\n", encoded_image);

    /* Write the encoded image to a file */
    FILE *output_file = fopen("encoded_image.txt", "w");
    if (!output_file) {
        fprintf(stderr, "Failed to open output file.\n");
        free(image_data);
        free(encoded_image);
        return;
    }

    fputs(encoded_image, output_file);
    fclose(output_file);

    free(image_data);
    free(encoded_image);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_image(argv[1]);

    return EXIT_SUCCESS;
}