#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void base64_encode(const unsigned char *src, size_t len, char *out) {
    static const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i, j;
    size_t olen;

    olen = 4 * ((len + 2) / 3); // output length
    if (olen < len) return; // integer overflow

    for (i = 0, j = 0; i < len;) {
        unsigned octet_a = i < len ? src[i++] : 0;
        unsigned octet_b = i < len ? src[i++] : 0;
        unsigned octet_c = i < len ? src[i++] : 0;

        out[j++] = table[(octet_a >> 2) & 0x3F];
        out[j++] = table[((octet_a << 4) | (octet_b >> 4)) & 0x3F];
        out[j++] = table[((octet_b << 2) | (octet_c >> 6)) & 0x3F];
        out[j++] = table[octet_c & 0x3F];
    }

    while (j < olen) {
        out[j++] = '=';
    }
    out[j] = '\0'; // null-terminate string
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *imageData = malloc(length);
    if (!imageData) {
        fclose(file);
        return;
    }

    fread(imageData, 1, length, file);
    fclose(file);

    size_t base64_length = 4 * ((length + 2) / 3) + 1; // +1 for null terminator
    char *base64_data = malloc(base64_length);
    if (!base64_data) {
        free(imageData);
        return;
    }

    base64_encode(imageData, length, base64_data);

    FILE *outFile = fopen("encoded_image.txt", "wb");
    if (outFile) {
        fwrite(base64_data, 1, strlen(base64_data), outFile);
        fclose(outFile);
    }

    free(imageData);
    free(base64_data);
}

int main() {
    upload_image("input_image.png"); // Replace with actual image filename
    return 0;
}