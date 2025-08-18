#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
int base64_decode(const char *input, unsigned char **output);
void upload_image(const char *base64_data);

int main() {
    // Example usage
    const char *example_base64_data = "iVBORw0KGgoAAAANSUhEUgAAAAUA"
                                      "AAAFCAYAAACNbyblAAAAHElEQVQI12P4//8/w38GIAXDIBKE0DHx"
                                      "gljNBAAO9TXL0Y4OHwAAAABJRU5ErkJggg=="; // A small sample image in base64

    upload_image(example_base64_data);

    return 0;
}

void upload_image(const char *base64_data) {
    unsigned char *decoded_data = NULL;

    if (base64_decode(base64_data, &decoded_data)) {
        FILE *file = fopen("output_image.bin", "wb");
        if (file != NULL) {
            fwrite(decoded_data, 1, strlen((const char *)decoded_data), file);
            fclose(file);
            printf("Image uploaded and saved successfully.\n");
        } else {
            fprintf(stderr, "Failed to open file for writing.\n");
        }
        
        free(decoded_data);
    } else {
        fprintf(stderr, "Base64 decoding failed.\n");
    }
}

// Helper function to decode base64
int base64_decode(const char *input, unsigned char **output) {
    static const char base64_chars[] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    int i, j;
    int in_len = strlen(input);
    int out_len = 0;
    for (i = 0; i < in_len; ++i)
        if (input[i] != '=') {
            const char *p = strchr(base64_chars, input[i]);
            if (!p) return 0; // Invalid character
            out_len++;
        }

    size_t buffer_size = ((out_len + 3) / 4) * 3;
    *output = malloc(buffer_size);
    if (*output == NULL) return 0;

    for (i = 0, j = 0; i < in_len;) {
        uint32_t sextet_a = input[i] == '=' ? 0 & i++ : strchr(base64_chars, input[i++]) - base64_chars;
        uint32_t sextet_b = input[i] == '=' ? 0 & i++ : strchr(base64_chars, input[i++]) - base64_chars;
        uint32_t sextet_c = input[i] == '=' ? 0 & i++ : strchr(base64_chars, input[i++]) - base64_chars;
        uint32_t sextet_d = input[i] == '=' ? 0 & i++ : strchr(base64_chars, input[i++]) - base64_chars;

        uint32_t triple = (sextet_a << 18) | (sextet_b << 12) | 
                          (sextet_c << 6) | sextet_d;

        if (j < buffer_size) (*output)[j++] = (triple >> 16) & 0xFF;
        if (j < buffer_size && input[i - 1] != '=') (*output)[j++] = (triple >> 8) & 0xFF;
        if (j < buffer_size && i - 2 > 0 && input[i - 2] != '=') (*output)[j++] = triple & 0xFF;
    }

    return 1;
}