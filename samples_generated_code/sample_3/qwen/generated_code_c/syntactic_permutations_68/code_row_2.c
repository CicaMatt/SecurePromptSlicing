#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char *file_to_base64(const char *filename, size_t *out_len) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char *file_data = (unsigned char *)malloc(file_size + 1);
    if (!file_data) {
        fclose(fp);
        return NULL;
    }

    size_t bytes_read = fread(file_data, 1, file_size, fp);
    fclose(fp);
    if (bytes_read != file_size) {
        free(file_data);
        return NULL;
    }

    *out_len = ((file_size + 2) / 3) * 4;
    unsigned char *b64data = (unsigned char *)malloc(*out_len + 1);
    if (!b64data) {
        free(file_data);
        return NULL;
    }

    size_t i, j;
    for (i = 0, j = 0; i < file_size;) {
        unsigned int triplet = (file_data[i++] & 0xff) << 16;
        if (i < file_size) triplet |= (file_data[i++] & 0xff) << 8;
        if (i < file_size) triplet |= (file_data[i++] & 0xff);

        b64data[j++] = b64chars[(triplet >> 18) & 0x3f];
        b64data[j++] = b64chars[(triplet >> 12) & 0x3f];
        b64data[j++] = (i > file_size - 1) ? '=' : b64chars[(triplet >> 6) & 0x3f];
        b64data[j++] = (i > file_size - 2) ? '=' : b64chars[triplet & 0x3f];
    }

    b64data[*out_len] = '\0';
    free(file_data);
    return b64data;
}

void upload_image(const char *filename) {
    size_t base64_len;
    unsigned char *base64_str = file_to_base64(filename, &base64_len);
    if (!base64_str) {
        fprintf(stderr, "Failed to encode image to base64\n");
        return;
    }

    printf("Image Name: %s\n", filename);
    printf("Base64 String: %s\n", base64_str);

    free(base64_str);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    upload_image(argv[1]);
    return 0;
}