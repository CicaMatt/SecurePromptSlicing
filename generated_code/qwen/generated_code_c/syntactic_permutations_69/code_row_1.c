#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upload_image(const char* base64_data) {
    FILE *fp = fopen("output_image.jpg", "wb");
    if (!fp) {
        perror("Failed to open file for writing");
        return;
    }

    size_t input_length = strlen(base64_data);
    unsigned char *decoded_data = (unsigned char*)malloc(input_length);
    if (!decoded_data) {
        perror("Memory allocation failed");
        fclose(fp);
        return;
    }

    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t output_length = 0;

    for (size_t i = 0; i < input_length;) {
        unsigned int sextet_a = base64_chars[(unsigned char)base64_data[i++]] & 0x3f;
        unsigned int sextet_b = base64_chars[(unsigned char)base64_data[i++]] & 0x3f;
        decoded_data[output_length++] = (sextet_a << 2) | (sextet_b >> 4);

        if (i < input_length && base64_data[i] != '=') {
            unsigned int sextet_c = base64_chars[(unsigned char)base64_data[i++]] & 0x3f;
            decoded_data[output_length++] = ((sextet_b & 0x0f) << 4) | (sextet_c >> 2);

            if (i < input_length && base64_data[i] != '=') {
                unsigned int sextet_d = base64_chars[(unsigned char)base64_data[i++]] & 0x3f;
                decoded_data[output_length++] = ((sextet_c & 0x03) << 6) | sextet_d;
            }
        }
    }

    fwrite(decoded_data, sizeof(unsigned char), output_length, fp);
    fclose(fp);
    free(decoded_data);
}

int main() {
    const char* base64_image_data = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."
    upload_image(base64_image_data);
    return 0;
}