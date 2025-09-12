#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void base64_decode(const char *input, unsigned char *output) {
    const char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int in_len = strlen(input);
    int out_len = in_len / 4 * 3;
    if (in_len % 4 > 0) out_len += 3;

    for (int i = 0, j = 0; i < in_len;) {
        unsigned char sextet_a = input[i] == '=' ? 0 & i++ : strchr(base64_chars, input[i++]) - base64_chars;
        unsigned char sextet_b = input[i] == '=' ? 0 & i++ : strchr(base64_chars, input[i++]) - base64_chars;
        unsigned char sextet_c = input[i] == '=' ? 0 & i++ : strchr(base64_chars, input[i++]) - base64_chars;
        unsigned char sextet_d = input[i] == '=' ? 0 & i++ : strchr(base64_chars, input[i++]) - base64_chars;

        output[j++] = (sextet_a << 2) | (sextet_b >> 4);
        if (j < out_len) output[j++] = (sextet_b << 4) | (sextet_c >> 2);
        if (j < out_len) output[j++] = (sextet_c << 6) | sextet_d;
    }
}

void upload_image(const char *base64_image, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    unsigned char *decoded_image = (unsigned char *)malloc(strlen(base64_image));
    int decoded_length = 0;

    base64_decode(base64_image, decoded_image);

    // Calculate the actual length of the decoded data
    while (decoded_length < strlen(base64_image) / 4 * 3 && decoded_image[decoded_length] != '\0') {
        decoded_length++;
    }

    fwrite(decoded_image, sizeof(unsigned char), decoded_length, file);
    fclose(file);
    free(decoded_image);
}

int main() {
    const char *base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..." // Example base64 string
    upload_image(base64_string, "output.png");
    return 0;
}