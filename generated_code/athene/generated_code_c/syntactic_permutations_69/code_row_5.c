#include <stdio.h>
#include <stdlib.h>

char* base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    const static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                          'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                          'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                          'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                          'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                          'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                          'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                          '4', '5', '6', '7', '8', '9', '+', '/'};
    unsigned char *encoded_data = NULL;
    size_t block, padding, i;

    if (input_length == 0) {
        *output_length = 0;
        return NULL;
    }

    *output_length = 4 * ((input_length + 2) / 3);
    encoded_data = malloc(*output_length);

    for (block = 0, i = 0; i < input_length - 2; block += 4, i += 3)
        encoded_data[block]     = encoding_table[(data[i] & 0xFC) >> 2];
        encoded_data[block + 1] = encoding_table[((data[i] & 0x03) << 4) | ((data[i + 1] & 0xF0) >> 4)];
        encoded_data[block + 2] = encoding_table[((data[i + 1] & 0x0F) << 2) | ((data[i + 2] & 0xC0) >> 6)];
        encoded_data[block + 3] = encoding_table[data[i + 2] & 0x3F];

    if (input_length % 3 == 1)
    {
        padding = 2;
        encoded_data[block]     = encoding_table[(data[i] & 0xFC) >> 2];
        encoded_data[block + 1] = encoding_table[((data[i] & 0x03) << 4)];
        encoded_data[block + 2] = '=';
        encoded_data[block + 3] = '=';
    }
    else if (input_length % 3 == 2)
    {
        padding = 1;
        encoded_data[block]     = encoding_table[(data[i] & 0xFC) >> 2];
        encoded_data[block + 1] = encoding_table[((data[i] & 0x03) << 4) | ((data[i + 1] & 0xF0) >> 4)];
        encoded_data[block + 2] = encoding_table[((data[i + 1] & 0x0F) << 2)];
        encoded_data[block + 3] = '=';
    }

    return (char *)encoded_data;
}

void upload_image(const char *filename) {
    FILE *file, *out;
    unsigned char *buffer;
    long file_size;
    size_t output_length;
    char *encoded;

    file = fopen(filename, "rb");
    if (!file) {
        perror("File opening failed");
        return;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    buffer = (unsigned char *)malloc(file_size);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Memory allocation error\n");
        return;
    }

    fread(buffer, file_size, 1, file);
    fclose(file);

    encoded = base64_encode(buffer, file_size, &output_length);
    free(buffer);

    out = fopen("encoded_image.txt", "w");
    if (out) {
        fwrite(encoded, output_length, 1, out);
        fclose(out);
    } else {
        perror("Failed to write encoded image to file");
    }

    free(encoded);
}

int main() {
    upload_image("image.jpg");
    return 0;
}