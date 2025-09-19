#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upload_image(const char* encoded_image, const char* filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return;

    unsigned int len = strlen(encoded_image);
    unsigned char decoded[len];
    unsigned int j = 0;
    for (unsigned int i = 0; i < len; ) {
        unsigned int sextet_a = encoded_image[i] == '=' ? 0 & i++ : encoded_image[i] - 'A' < 26 ? encoded_image[i++] - 'A'          : encoded_image[i] - 'a' < 26 ? encoded_image[i++] - 'a' + 26 : encoded_image[i] - '0' < 10 ? encoded_image[i++] + 52 : encoded_image[i++] - '!' + 62;
        unsigned int sextet_b = encoded_image[i] == '=' ? 0 & i++ : encoded_image[i] - 'A' < 26 ? encoded_image[i++] - 'A'          : encoded_image[i] - 'a' < 26 ? encoded_image[i++] - 'a' + 26 : encoded_image[i] - '0' < 10 ? encoded_image[i++] + 52 : encoded_image[i++] - '!' + 62;
        unsigned int sextet_c = encoded_image[i] == '=' ? 0 & i++ : encoded_image[i] - 'A' < 26 ? encoded_image[i++] - 'A'          : encoded_image[i] - 'a' < 26 ? encoded_image[i++] - 'a' + 26 : encoded_image[i] - '0' < 10 ? encoded_image[i++] + 52 : encoded_image[i++] - '!' + 62;
        unsigned int sextet_d = encoded_image[i] == '=' ? 0 & i++ : encoded_image[i] - 'A' < 26 ? encoded_image[i++] - 'A'          : encoded_image[i] - 'a' < 26 ? encoded_image[i++] - 'a' + 26 : encoded_image[i] - '0' < 10 ? encoded_image[i++] + 52 : encoded_image[i++] - '!' + 62;

        decoded[j++] = (sextet_a << 2) | (sextet_b >> 4);
        if (j < len) decoded[j++] = (sextet_b << 4) | (sextet_c >> 2);
        if (j < len) decoded[j++] = (sextet_c << 6) | sextet_d;
    }

    fwrite(decoded, sizeof(unsigned char), j, fp);
    fclose(fp);
}

int main() {
    const char* encoded_image = "iVBORw0KGgoAAAANSUhEUgAAAAUA..." // Base64 encoded image data
    upload_image(encoded_image, "output.png");
    return 0;
}