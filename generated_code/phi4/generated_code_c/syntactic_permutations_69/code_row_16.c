#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple Base64 encoding table
static const char base64_table[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

void encode_base64(const unsigned char *data, size_t input_length, char **encoded_data) {
    // Allocate memory for the encoded data
    size_t output_length = 4 * ((input_length + 2) / 3);
    *encoded_data = (char *)malloc(output_length + 1); // +1 for null terminator

    if (*encoded_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int i, j;
    unsigned char temp[3];
    size_t index = 0;

    for (i = 0; i < input_length;) {
        // Read up to three bytes from the input data
        memset(temp, 0, sizeof(temp));
        for (j = 0; j < 3 && i < input_length; ++i, ++j) {
            temp[j] = data[i];
        }

        // Encode these three bytes into four base64 characters
        (*encoded_data)[index++] = base64_table[(temp[0] & 0xfc) >> 2];
        (*encoded_data)[index++] = base64_table[((temp[0] & 0x03) << 4) | ((temp[1] & 0xf0) >> 4)];
        (*encoded_data)[index++] = (i > input_length - 1) ? '=' : base64_table[((temp[1] & 0x0f) << 2) | ((temp[2] & 0xc0) >> 6)];
        (*encoded_data)[index++] = (i > input_length - 2) ? '=' : base64_table[temp[2] & 0x3f];
    }

    (*encoded_data)[output_length] = '\0'; // Null terminate the string
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return;
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    char *encoded_data = NULL;
    encode_base64(buffer, file_size, &encoded_data);

    printf("Encoded Image (Base64):\n%s\n", encoded_data);

    free(buffer);
    free(encoded_data);
}

int main() {
    const char *filename = "example_image.jpg"; // Replace with your image filename
    upload_image(filename);
    return 0;
}