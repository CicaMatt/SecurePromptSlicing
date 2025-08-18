#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encode a string in base64
void base64_encode(const unsigned char *input, size_t input_len, char *output) {
    static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i = 0, j = 0;
    size_t len = 0;

    while (len < input_len) {
        unsigned int bits = (input[len++] & 0xff) << 16;
        if (len < input_len) bits |= (input[len++] & 0xff) << 8;
        if (len < input_len) bits |= (input[len++] & 0xff);

        output[j++] = b64[(bits >> 18) & 0x3f];
        output[j++] = b64[(bits >> 12) & 0x3f];
        output[j++] = (len < input_len + 2) ? b64[(bits >> 6) & 0x3f] : '=';
        output[j++] = (len < input_len + 1) ? b64[bits & 0x3f] : '=';
    }
    output[j] = '\0';
}

void upload_image(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    // Calculate the size of the base64 encoded string
    size_t output_len = ((file_size + 2) / 3) * 4 + 1;
    char *base64_output = (char *)malloc(output_len);
    if (!base64_output) {
        perror("Failed to allocate memory");
        free(buffer);
        return;
    }

    base64_encode(buffer, file_size, base64_output);

    // Output the base64 encoded string
    printf("Encoded image: %s\n", base64_output);

    free(base64_output);
    free(buffer);
}

int main() {
    const char *file_path = "path_to_your_image.jpg"; // Replace with your image path
    upload_image(file_path);
    return 0;
}