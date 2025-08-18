#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_base64(unsigned char *input, size_t input_len, unsigned char *output) {
    int i = 0, j = 0;
    while (i < input_len) {
        unsigned char o0 = (input[i++] & 0xFC) >> 2;
        unsigned char o1 = ((input[i-1] & 0x03) << 4);
        if (i < input_len) o1 |= (input[i] & 0xF0) >> 4;
        unsigned char o2 = ((input[i-1] & 0x0F) << 2);
        if (i+1 < input_len) o2 |= (input[i++] & 0xC0) >> 6;
        unsigned char o3 = (input[i-1] & 0x3F);

        output[j++] = base64_table[o0];
        output[j++] = base64_table[o1];
        if (i < input_len+1) output[j++] = base64_table[o2];
        if (i < input_len+2) output[j++] = base64_table[o3];
    }
    while ((j % 4) != 0) {
        output[j++] = '=';
    }
    output[j] = '\0';
}

void upload_image(const char *image_path, const char *output_file_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) return;

    fseek(file, 0, SEEK_END);
    long file_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_len + 1);
    fread(buffer, file_len, 1, file);
    fclose(file);

    size_t base64_length = ((file_len + 2) / 3) * 4;
    unsigned char *base64_output = (unsigned char *)malloc(base64_length + 1);

    encode_base64(buffer, file_len, base64_output);

    FILE *output_file = fopen(output_file_path, "wb");
    if (!output_file) {
        free(buffer);
        free(base64_output);
        return;
    }

    fwrite(base64_output, base64_length, 1, output_file);
    fclose(output_file);

    free(buffer);
    free(base64_output);
}

int main() {
    upload_image("input.jpg", "output.txt");
    return 0;
}