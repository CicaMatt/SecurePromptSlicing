#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encode data to Base64
void *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t result_size = 4 * ((input_length + 2) / 3);
    char *result = (char *)malloc(result_size + 1);
    if (!result) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        result[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        result[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        result[j++] = base64_chars[(triple >> 1 * 6) & 0x3F];
        result[j++] = base64_chars[(triple >> 0 * 6) & 0x3F];
    }

    for (size_t i = 0, j = result_size; i < (3 - input_length % 3) % 3; i++, j--) {
        result[j] = '=';
    }

    result[result_size] = '\0';
    *output_length = result_size;
    return result;
}

void upload_image(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_len + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return;
    }

    fread(buffer, file_len, 1, file);
    fclose(file);

    size_t base64_length;
    char *base64_data = (char *)base64_encode(buffer, file_len, &base64_length);
    free(buffer);

    if (!base64_data) {
        perror("Failed to encode data");
        return;
    }

    FILE *output_file = fopen("encoded_image.txt", "w");
    if (!output_file) {
        perror("Failed to open output file");
        free(base64_data);
        return;
    }

    fwrite(base64_data, base64_length, 1, output_file);
    fclose(output_file);

    free(base64_data);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

    upload_image(argv[1]);

    return 0;
}