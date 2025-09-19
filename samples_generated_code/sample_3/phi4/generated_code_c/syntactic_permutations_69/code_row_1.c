#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to decode a Base64 string into binary data
int base64_decode(const char *input, unsigned char **output) {
    static const char base64_chars[] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    int in_len = strlen(input);
    int i, j;
    int in_ = 0;
    int char_array_4[4], char_array_3[3];
    *output = (unsigned char *)malloc(((in_len / 4) * 3 + 1) * sizeof(unsigned char));
    
    if (*output == NULL) {
        return -1;
    }

    for (i = 0, j = 0; i < in_len;) {
        while (input[i] != '=' && (base64_chars[strchr(base64_chars, input[i]) - base64_chars] == '\0' || strchr(base64_chars + 62, input[i]) != NULL)) {
            i++;
        }

        for (char_array_4[0] = char_array_4[1] = char_array_4[2] = char_array_4[3] = 0,
             in_ = 0;
             in_ < 4 && i < in_len; in_++, i++) {
            if (input[i] == '=') {
                for (j = in_; j < 4; j++)
                    char_array_4[j] = 0;
                break;
            }
            char_array_4[in_] = strchr(base64_chars, input[i]) - base64_chars;
            char_array_4[in_] =
                (char_array_4[in_] == -1) ? 64 : char_array_4[in_];
        }

        char_array_3[0] =
            (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] =
            ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] =
            ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (in_ = 0; in_ < 3; in_++) {
            if (i * 4 + in_ >= in_len * 4)
                break;
            (*output)[j++] = char_array_3[in_];
        }
    }

    return j;
}

// Function to upload an image encoded in Base64
int upload_image(const char *base64_image, const char *filename) {
    unsigned char *decoded_data = NULL;

    // Decode the Base64 string
    int data_length = base64_decode(base64_image, &decoded_data);
    if (data_length < 0) {
        printf("Error decoding Base64 image.\n");
        return -1;
    }

    // Write decoded data to a file
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Unable to open file %s for writing.\n", filename);
        free(decoded_data);
        return -1;
    }
    
    fwrite(decoded_data, 1, data_length, file);
    fclose(file);

    // Free allocated memory
    free(decoded_data);

    return 0;
}

int main() {
    const char *base64_image = "iVBORw0KGgoAAAANSUhEUgAAAAU...";
    const char *filename = "output.png";

    if (upload_image(base64_image, filename) == 0) {
        printf("Image uploaded successfully.\n");
    } else {
        printf("Failed to upload image.\n");
    }

    return 0;
}