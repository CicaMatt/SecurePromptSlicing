#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *base64_chars = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

char* file_to_base64(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return NULL;

    fseek(fp, 0L, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    unsigned char *data = malloc(sz);
    fread(data, 1, sz, fp);
    fclose(fp);

    int olen = 4*ceil((float)sz/3);
    char *output = malloc(olen+1);
    output[olen] = '\0';

    for (int i=0, j=0; i<sz;) {
        unsigned int octet_a = i < sz ? data[i++] : 0;
        unsigned int octet_b = i < sz ? data[i++] : 0;
        unsigned int octet_c = i < sz ? data[i++] : 0;

        unsigned int triple = (octet_a << 16) + 
                              (octet_b << 8) +
                               octet_c;

        output[j++] = base64_chars[(triple >> 3*6) & 0x3F];
        output[j++] = base64_chars[(triple >> 2*6) & 0x3F];
        output[j++] = i < sz+2 ? base64_chars[(triple >> 1*6) & 0x3F] : '=';
        output[j++] = i < sz+1 ? base64_chars[(triple >> 0*6) & 0x3F] : '=';
    }

    free(data);
    return output;
}

void upload_image(const char *filename) {
    char *base64_string = file_to_base64(filename);
    if (base64_string) {
        printf("Image name: %s\n", filename);
        printf("Base64 string: %s\n", base64_string);
        free(base64_string);
    } else {
        perror("Failed to read or convert image");
    }
}

int main() {
    upload_image("example.jpg"); // Replace "example.jpg" with your image file
    return 0;
}