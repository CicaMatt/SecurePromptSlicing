#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

void encode_base64(const unsigned char *data, size_t input_length, char *encoded_data) {
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

            for (i = 0; i < 4; i++)
                encoded_data[j++] = base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (int k = i; k < 3; k++) char_array_3[k] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (int k = 0; k < i + 1; k++)
            encoded_data[j++] = base64_chars[char_array_4[k]];
        while (i++ < 3)
            encoded_data[j++] = '=';
    }

    encoded_data[j] = '\0';
}

void upload_image(const char *image_path, const char *output_file) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    fread(buffer, sizeof(unsigned char), file_size, file);
    fclose(file);

    // Encode the image data to base64
    char *encoded_data = (char *)malloc((4 * ((file_size + 2) / 3)) + 1);
    encode_base64(buffer, file_size, encoded_data);

    free(buffer);

    // Write the encoded data to a file
    FILE *output = fopen(output_file, "w");
    if (!output) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    fprintf(output, "%s", encoded_data);
    fclose(output);

    free(encoded_data);
}

int main() {
    const char *image_path = "example.jpg";
    const char *encoded_file = "encoded_image.txt";

    upload_image(image_path, encoded_file);

    return 0;
}