#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include necessary headers for Base64 encoding/decoding
#define BASE64_ENCODED_LEN 4
#define BASE64_DECODED_LEN 3

int base64_decode_length(const char *input) {
    int len = strlen(input);
    return ((len + 3) / 4) * 3;
}

void base64_decode(const unsigned char *in, size_t in_len, unsigned char *out) {
    static const unsigned char decoding_table[256] = {
        /* Fill with the appropriate values */
        [/* Add the correct Base64 decoding table here */]
    };

    if (in_len % 4 != 0) return;

    for (size_t i = 0, j = 0; i < in_len;) {
        unsigned char a = decoding_table[in[i++]];
        unsigned char b = decoding_table[in[i++]];
        unsigned char c = decoding_table[in[i++]];

        if (a == -1 || b == -1) break;
        
        out[j++] = (a << 2) | ((b & 0x30) >> 4);
        if (c == -1) break;

        out[j++] = ((b & 0xf) << 4) | ((c & 0x3c) >> 2);

        unsigned char d = decoding_table[in[i++]];
        if (d == -1) break;
        
        out[j++] = ((c & 0x03) << 6) | d;
    }
}

void upload_image(const char *base64_image, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    size_t decoded_len = base64_decode_length(base64_image);
    unsigned char *decoded_data = malloc(decoded_len + 1); // Plus one for null-termination
    if (!decoded_data) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return;
    }

    base64_decode((const unsigned char *)base64_image, strlen(base64_image), decoded_data);

    fwrite(decoded_data, 1, decoded_len, file);

    free(decoded_data);
    fclose(file);
}

int main() {
    const char *base64_image = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // Example Base64 string
    upload_image(base64_image, "output.png");
    
    return 0;
}