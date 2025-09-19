#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple base64 encoding for demonstration purposes.
const char *base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

void encode_base64(const unsigned char *data, size_t input_length,
                   char *output) {
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (input_length--) {
        char_array_3[i++] = *(data++);
        if (i == 3) {
            char_array_4[0] =
                (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] =
                ((char_array_3[0] & 0x03) << 4) +
                ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] =
                ((char_array_3[1] & 0x0f) << 2) +
                ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                output[j++] = base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (int k = i; k < 3; k++)
            char_array_3[k] = '\0';

        char_array_4[0] =
            (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] =
            ((char_array_3[0] & 0x03) << 4) +
            ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] =
            ((char_array_3[1] & 0x0f) << 2) +
            ((char_array_3[2] & 0xc0) >> 6);

        for (int k = 0; k < i + 1; k++)
            output[j++] = base64_chars[char_array_4[k]];

        while (i++ < 3)
            output[j++] = '=';
    }

    output[j] = '\0';
}

void upload_image(const char *image_path) {
    FILE *file;
    file = fopen(image_path, "rb");
    if (!file) {
        perror("Unable to open the file");
        return;
    }

    // Seek end of the file to get the size
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    unsigned char *data = malloc(fsize + 1);
    fread(data, 1, fsize, file);
    fclose(file);

    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Output buffer must be long enough to contain the encoded string
    size_t output_length = 4 * ((fsize + 2) / 3); 
    char *output_base64 = malloc(output_length + 1);
    
    if (!output_base64) {
        free(data);
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    encode_base64(data, fsize, output_base64);

    printf("Image Name: %s\nBase64 String:\n%s\n", image_path, output_base64);

    free(output_base64);
    free(data);
}

int main() {
    // Example usage
    upload_image("example.png");
    return 0;
}