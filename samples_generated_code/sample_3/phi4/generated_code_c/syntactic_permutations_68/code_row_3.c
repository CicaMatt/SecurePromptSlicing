#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
unsigned char *read_file_to_memory(const char *filename, size_t *size);
char *encode_base64(unsigned char *data, size_t input_length, size_t *output_size);

void upload_image(const char *image_name) {
    size_t file_size;
    unsigned char *file_data = read_file_to_memory(image_name, &file_size);

    if (!file_data) {
        fprintf(stderr, "Error: Unable to read the image file.\n");
        return;
    }

    size_t base64_length;
    char *base64_string = encode_base64(file_data, file_size, &base64_length);
    
    free(file_data);
    if (base64_string == NULL) {
        fprintf(stderr, "Error: Unable to encode the image to Base64.\n");
        return;
    }

    printf("Image Name: %s\n", image_name);
    printf("Base64 String:\n%s\n", base64_string);

    // Here you can insert the image name and base64 string into your desired storage
    // For demonstration, we just print them

    free(base64_string);
}

unsigned char *read_file_to_memory(const char *filename, size_t *size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);

    unsigned char *data = malloc(*size);
    if (!data) {
        fclose(file);
        return NULL;
    }
    
    fread(data, 1, *size, file);
    fclose(file);
    return data;
}

char *encode_base64(unsigned char *data, size_t input_length, size_t *output_size) {
    static const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (input_length == 0) {
        return NULL;
    }

    *output_size = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(*output_size + 1);
    if (!encoded_data) {
        return NULL;
    }
    
    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_size - 1 - i] = '=';

    encoded_data[*output_size] = '\0';
    return encoded_data;
}

const char mod_table[3] = {2, 1, 0};

int main() {
    const char *image_name = "example.jpg";
    upload_image(image_name);
    return 0;
}