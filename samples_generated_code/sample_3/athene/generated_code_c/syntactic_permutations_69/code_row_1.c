#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    static const char encoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    *output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(*output_length + 1);
    if (encoded_data == NULL) return NULL;
    size_t input_part = 0, input_index = 0, output_index = 0;
    unsigned char octet_a = 0, octet_b = 0, octet_c = 0;

    while (input_length--) {
        switch(input_part % 3) {
            case 0:
                octet_a = *(data + input_index++);
                encoded_data[output_index++] = encoding[(octet_a & 0xFC) >> 2];
                break;
            case 1:
                octet_b = *(data + input_index++);
                encoded_data[output_index++] = encoding[((octet_a & 0x03) << 4) | ((octet_b & 0xF0) >> 4)];
                break;
            case 2:
                octet_c = *(data + input_index++);
                encoded_data[output_index++] = encoding[((octet_b & 0x0F) << 2) | ((octet_c & 0xC0) >> 6)];
                encoded_data[output_index++] = encoding[octet_c & 0x3F];
                break;
        }
        input_part++;
    }

    while (input_part++ % 3)
        encoded_data[output_index++] = '=';

    encoded_data[*output_length] = '\0';
    return encoded_data;
}

size_t base64_decode(const char *data, size_t input_length, unsigned char **output) {
    static const int decoding[] = {62,-1,-1,-1,63,52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-2,-1,-1,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
    const int decoded_size = input_length / 4 * 3 + (input_length % 4 ? input_length % 4 - 1 : 0);
    *output = malloc(decoded_size);
    if (*output == NULL) return 0;
    size_t output_index = 0, i = 0;

    while (i < input_length) {
        int sextet_a = data[i] == '=' ? 0 & i++ : decoding[(unsigned char)data[i++]];
        int sextet_b = data[i] == '=' ? 0 & i++ : decoding[(unsigned char)data[i++]];
        *output[output_index++] = (sextet_a << 2) | (sextet_b >> 4);

        if (i < input_length && data[i] != '=') {
            int sextet_c = decoding[(unsigned char)data[i++]];
            *output[output_index++] = ((sextet_b & 0xf) << 4) | (sextet_c >> 2);
        }

        if (i < input_length && data[i] != '=') {
            int sextet_d = decoding[(unsigned char)data[i++]];
            *output[output_index++] = ((sextet_c & 0x3) << 6) | sextet_d;
        }
    }

    return output_index;
}

void upload_image(const char *file_path, const char *output_file) {
    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    fread(buffer, 1, file_size, fp);
    fclose(fp);

    size_t encoded_length;
    char *encoded_data = base64_encode(buffer, file_size, &encoded_length);

    FILE *out_fp = fopen(output_file, "wb");
    if (out_fp == NULL) {
        perror("Error opening output file");
        free(encoded_data);
        free(buffer);
        exit(1);
    }
    fwrite(encoded_data, 1, encoded_length, out_fp);
    fclose(out_fp);

    unsigned char *decoded_data;
    size_t decoded_length = base64_decode(encoded_data, encoded_length, &decoded_data);

    FILE *decoded_fp = fopen("decoded_image.jpg", "wb");
    if (decoded_fp == NULL) {
        perror("Error opening decoded file");
        free(decoded_data);
        free(encoded_data);
        free(buffer);
        exit(1);
    }
    fwrite(decoded_data, 1, decoded_length, decoded_fp);
    fclose(decoded_fp);

    free(decoded_data);
    free(encoded_data);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_image> <output_file>\n", argv[0]);
        exit(1);
    }
    upload_image(argv[1], argv[2]);
    return 0;
}