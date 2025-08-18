#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper functions declarations
void encode_base64(const unsigned char *data, size_t input_length, char *output);
size_t write_to_file(const char *file_name, const char *content);

int upload_image(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Error opening the input file");
        return -1;
    }

    fseek(input_file, 0, SEEK_END);
    size_t data_size = ftell(input_file);
    rewind(input_file);

    unsigned char *buffer = (unsigned char *)malloc(data_size);
    if (!buffer) {
        fclose(input_file);
        perror("Error allocating memory");
        return -1;
    }

    fread(buffer, 1, data_size, input_file);
    fclose(input_file);

    size_t encoded_length = 4 * ((data_size + 2) / 3); // Calculate length of base64 output
    char *encoded_data = (char *)malloc(encoded_length + 1);
    if (!encoded_data) {
        free(buffer);
        perror("Error allocating memory for base64 encoding");
        return -1;
    }

    encode_base64(buffer, data_size, encoded_data);

    size_t write_result = write_to_file(output_filename, encoded_data);
    free(buffer);
    free(encoded_data);

    if (write_result != 0) {
        fprintf(stderr, "Error writing to file\n");
        return -1;
    }

    return 0;
}

void encode_base64(const unsigned char *data, size_t input_length, char *output) {
    static const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i, j, k;

    for (i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        output[j++] = encoding_table[(triple >> 18) & 0x3F];
        output[j++] = encoding_table[(triple >> 12) & 0x3F];
        output[j++] = i > input_length + 1 ? '=' : encoding_table[(triple >> 6) & 0x3F];
        output[j++] = i > input_length ? '=' : encoding_table[triple & 0x3F];
    }
    output[j] = '\0';
}

size_t write_to_file(const char *file_name, const char *content) {
    FILE *output_file = fopen(file_name, "w");
    if (!output_file) {
        perror("Error opening the output file");
        return -1;
    }

    size_t written_size = fwrite(content, 1, strlen(content), output_file);
    fclose(output_file);

    return (written_size == strlen(content)) ? 0 : -1;
}

int main() {
    const char *input_filename = "input_image.png";
    const char *output_filename = "encoded_image.txt";

    if (upload_image(input_filename, output_filename) != 0) {
        fprintf(stderr, "Failed to upload image\n");
        return EXIT_FAILURE;
    }

    printf("Image uploaded and encoded successfully.\n");

    return EXIT_SUCCESS;
}