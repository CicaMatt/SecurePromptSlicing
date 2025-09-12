#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Function prototypes
void upload_image(const char *filename);
size_t file_size(FILE *f);
char* read_file_to_base64(const char *filename, size_t *out_length);

int main() {
    const char *filename = "example.jpg";
    upload_image(filename);
    return 0;
}

void upload_image(const char *filename) {
    size_t base64_len;
    char *base64_data = read_file_to_base64(filename, &base64_len);

    if (base64_data != NULL) {
        printf("Image Name: %s\n", filename);
        printf("Base64 String:\n%s\n", base64_data);

        free(base64_data);
    } else {
        fprintf(stderr, "Failed to read image file.\n");
    }
}

size_t file_size(FILE *f) {
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    rewind(f);
    return size;
}

char* read_file_to_base64(const char *filename, size_t *out_length) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    size_t length = file_size(file);
    unsigned char *buffer = (unsigned char *)malloc(length);

    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    fread(buffer, 1, length, file);
    fclose(file);

    // Base64 encoding
    static const char base64_chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    size_t out_size = 4 * ((length + 2) / 3);
    char *encoded_data = (char *)malloc(out_size + 1);

    if (!encoded_data) {
        free(buffer);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    for (size_t i = 0; i < length; i += 3) {
        uint32_t octet_a = buffer[i];
        uint32_t octet_b = (i + 1 < length) ? buffer[i + 1] : 0;
        uint32_t octet_c = (i + 2 < length) ? buffer[i + 2] : 0;

        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        encoded_data[(i / 3) * 4]     = base64_chars[(triple >> 18) & 63];
        encoded_data[(i / 3) * 4 + 1] = base64_chars[(triple >> 12) & 63];
        encoded_data[(i / 3) * 4 + 2] = (i + 1 < length) ? base64_chars[(triple >> 6) & 63] : '=';
        encoded_data[(i / 3) * 4 + 3] = (i + 2 < length) ? base64_chars[triple & 63] : '=';

        if (i >= length - 2) break;
    }
    
    encoded_data[out_size] = '\0';
    free(buffer);
    
    *out_length = out_size;
    return encoded_data;
}