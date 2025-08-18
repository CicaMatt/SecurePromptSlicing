#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE64_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

void encode_block(unsigned char input[3], unsigned char output[4], int len) {
    unsigned char buffer[4];
    memset(buffer, 0, sizeof(buffer));
    memcpy(buffer, input, len);

    output[0] = BASE64_ALPHABET[(buffer[0] & 0xFC) >> 2];
    output[1] = BASE64_ALPHABET[((buffer[0] & 0x03) << 4) | ((buffer[1] & 0xF0) >> 4)];
    if (len > 1) {
        output[2] = BASE64_ALPHABET[((buffer[1] & 0x0F) << 2) | ((buffer[2] & 0xC0) >> 6)];
    } else {
        output[2] = '=';
    }
    if (len > 2) {
        output[3] = BASE64_ALPHABET[buffer[2] & 0x3F];
    } else {
        output[3] = '=';
    }
}

void upload_image(const char *input_path, const char *output_path) {
    FILE *infile = fopen(input_path, "rb");
    if (!infile) return;

    FILE *outfile = fopen(output_path, "w");
    if (!outfile) {
        fclose(infile);
        return;
    }

    unsigned char in[3], out[4];
    size_t read_count;
    int len = 0;

    while ((read_count = fread(in + len, 1, 3 - len, infile)) > 0) {
        encode_block(in, out, (len += read_count));
        fwrite(out, 1, 4, outfile);
        if (read_count < 3 - len) break;
        len -= 3;
    }

    fclose(infile);
    fclose(outfile);
}