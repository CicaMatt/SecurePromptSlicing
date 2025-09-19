#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decode_base64(const char *input, const size_t length, unsigned char **output) {
    static int decTable[256];
    if (!decTable[0]) {
        for (int i = 0; i < 64; ++i)
            decTable['A' + i] = i;
        for (int i = 0; i < 26; ++i)
            decTable['a' + i] = i;
        for (int i = 0; i < 10; ++i)
            decTable['0' + i] = i + 52;
        decTable['+'] = 62;
        decTable['/'] = 63;
    }

    int padding = 0;
    if (input[length - 1] == '=')
        padding++;
    if (input[length - 2] == '=')
        padding++;

    size_t outputLen = ((length * 4) / 6) - padding;
    *output = malloc(outputLen);

    for (int i = 0, j = 0; i < length;) {
        uint32_t sextet_a = input[i] == '\n' ? i++ : decTable[(unsigned char)input[i++]];
        uint32_t sextet_b = input[i] == '\n' ? i++ : decTable[(unsigned char)input[i++]];
        uint32_t sextet_c = input[i] == '\n' ? 0 : decTable[(unsigned char)input[i++]];
        uint32_t sextet_d = input[i] == '\n' ? 0 : decTable[(unsigned char)input[i++]];

        uint32_t triple = (sextet_a << 18) | (sextet_b << 12) | (sextet_c << 6) | sextet_d;

        if (j < outputLen)
            (*output)[j++] = (triple >> 16) & 0xFF;
        if (j < outputLen && i - padding)
            (*output)[j++] = (triple >> 8) & 0xFF;
        if (j < outputLen && i - padding * 2)
            (*output)[j++] = triple & 0xFF;
    }
}

void upload_image(const char *base64_image, const char *filename) {
    size_t image_len = strlen(base64_image);
    unsigned char *image_data;

    decode_base64(base64_image, image_len, &image_data);

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        free(image_data);
        return;
    }

    fwrite(image_data, 1, strlen((const char *)image_data), file);
    fclose(file);

    free(image_data);
}

int main() {
    const char *base64_image = "iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAAHElEQVQI12P4//8/w38GIAXDIBKE"
                               "0DHxgljNBAAO9TXL0Y4OHwAAAABJRU5ErkJggg==";
    const char *filename = "output_image.png";

    upload_image(base64_image, filename);

    return 0;
}