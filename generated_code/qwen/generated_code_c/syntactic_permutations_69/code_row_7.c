#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encode data to Base64
char* base64_encode(const unsigned char* data, size_t input_length) {
    static const char encoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char* encoded_data = (char*)malloc(4 * ((input_length + 2) / 3) + 1);
    if (!encoded_data) return NULL;
    size_t output_length = 0;

    for (size_t i = 0; i < input_length; ) {
        unsigned int octet_a = i < input_length ? data[i++] : 0;
        unsigned int octet_b = i < input_length ? data[i++] : 0;
        unsigned int octet_c = i < input_length ? data[i++] : 0;

        unsigned int triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded_data[output_length++] = encoding[(triple >> 3 * 6) & 0x3F];
        encoded_data[output_length++] = encoding[(triple >> 2 * 6) & 0x3F];
        encoded_data[output_length++] = encoding[(triple >> 1 * 6) & 0x3F];
        encoded_data[output_length++] = encoding[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 4 * ((input_length + 2) / 3); i < output_length; ++i)
        encoded_data[i] = '=';

    encoded_data[output_length] = '\0';

    return encoded_data;
}

void upload_image(const char* file_path, const char* output_file_path) {
    FILE* file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open image file");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(file_size);
    if (!buffer) {
        fclose(file);
        perror("Failed to allocate memory");
        return;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    fclose(file);

    if (bytes_read != file_size) {
        free(buffer);
        perror("Failed to read image file");
        return;
    }

    char* encoded_image = base64_encode(buffer, file_size);
    free(buffer);

    if (!encoded_image) {
        perror("Failed to encode image");
        return;
    }

    FILE* output_file = fopen(output_file_path, "w");
    if (!output_file) {
        free(encoded_image);
        perror("Failed to open output file");
        return;
    }

    fwrite(encoded_image, 1, strlen(encoded_image), output_file);
    fclose(output_file);

    free(encoded_image);
}

int main() {
    upload_image("input.jpg", "encoded_output.txt");
    return 0;
}