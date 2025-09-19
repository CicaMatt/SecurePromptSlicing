#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IMAGE_SIZE 1024 * 1024 // 1MB max image size

char* encode_base64(const unsigned char* src, size_t len);
void upload_image(const char* filename);

int main() {
    const char* filename = "example.jpg"; // Replace with actual file name
    upload_image(filename);
    return 0;
}

char* encode_base64(const unsigned char* src, size_t len) {
    static const char base64_chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    
    int out_len = (len + 2) / 3 * 4;
    char* out = malloc(out_len + 1);
    if (!out) return NULL;

    for (size_t i = 0, j = 0; i < len;) {
        unsigned int bits = (i + 2 < len) ? 
            (src[i++] << 16) + (src[i++] << 8) + src[i++] :
            (i + 1 < len) ?
            (src[i++] << 16) + (src[i++] << 8) :
            (src[i++] << 16);

        out[j++] = base64_chars[(bits >> 18) & 0x3F];
        out[j++] = base64_chars[(bits >> 12) & 0x3F];
        out[j++] = (i > len + 1) ? '=' : base64_chars[(bits >> 6) & 0x3F];
        out[j++] = (i > len)   ? '=' : base64_chars[bits & 0x3F];
    }
    out[out_len] = '\0';
    return out;
}

void upload_image(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    unsigned char buffer[MAX_IMAGE_SIZE];
    size_t len = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    if (len == 0 || ferror(file)) {
        fprintf(stderr, "Error reading file\n");
        return;
    }

    char* base64_image = encode_base64(buffer, len);
    if (!base64_image) {
        perror("Failed to allocate memory for base64 encoding");
        return;
    }

    // Insert image name and base64 string into database or other storage
    printf("Image Name: %s\n", filename);
    printf("Base64 Encoded Image:\n%s\n", base64_image);

    free(base64_image);
}