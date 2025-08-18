#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function prototypes
void encodeBase64(const unsigned char *data, size_t input_length, char *output);
size_t writeEncodedImageToFile(const char *filename, const char *encoded_data);

void upload_image(const char *input_filename, const char *output_filename) {
    FILE *file = fopen(input_filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    char *encoded_image = (char *)malloc((4 * ((file_size + 2) / 3)) + 1);
    if (!encoded_image) {
        perror("Memory allocation failed");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    encodeBase64(buffer, file_size, encoded_image);

    size_t written_bytes = writeEncodedImageToFile(output_filename, encoded_image);

    printf("Written %zu bytes to the output file.\n", written_bytes);

    free(buffer);
    free(encoded_image);
}

void encodeBase64(const unsigned char *data, size_t input_length, char *output) {
    static const char encoding_table[] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    int i, j;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    for (i = 0, j = 0; i < input_length;) {
        char_array_3[0] = data[i++];
        char_array_3[1] = i < input_length ? data[i++] : '\0';
        char_array_3[2] = i < input_length ? data[i++] : '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; j < 4; j++) {
            if (i > input_length + j - 1)
                output[j + i / 3 * 4 - 1] = '=';
            else
                output[j + i / 3 * 4 - 1] = encoding_table[char_array_4[j]];
        }
    }
}

size_t writeEncodedImageToFile(const char *filename, const char *encoded_data) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    size_t written_bytes = fwrite(encoded_data, sizeof(char), strlen(encoded_data), file);

    fclose(file);

    return written_bytes;
}

int main() {
    const char *input_filename = "input_image.png"; // Replace with your input image path
    const char *output_filename = "encoded_image.txt"; // Output file where the base64 encoded string will be saved

    upload_image(input_filename, output_filename);

    return 0;
}