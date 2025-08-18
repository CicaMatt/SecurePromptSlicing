#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h> // For sleep()
#endif

// Mock functions for demonstration purposes. Implement actual logic as needed.
unsigned char* read_image_to_bytes(const char *filename, size_t *out_size) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *data = malloc(fsize + 1);
    fread(data, 1, fsize, file);
    fclose(file);

    data[fsize] = 0;
    if (out_size) *out_size = fsize;

    return data;
}

char* convert_to_base64(const unsigned char *data, size_t input_length, size_t *output_length) {
    static const char encoding_table[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    if (input_length == 0) return NULL;

    *output_length = ((input_length + 2) / 3) * 4;
    char *encoded_data = malloc(*output_length + 1);
    unsigned long i = 0;
    unsigned long j = 0;

    while (i < input_length) {
        unsigned char octet_a = i < input_length ? data[i++] : 0;
        unsigned char octet_b = i < input_length ? data[i++] : 0;
        unsigned char octet_c = i < input_length ? data[i++] : 0;

        unsigned long triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        encoded_data[j++] = encoding_table[(triple >> 18) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 12) & 0x3F];
        encoded_data[j++] = i > input_length - 1 ? '=' : encoding_table[(triple >> 6) & 0x3F];
        encoded_data[j++] = i > input_length - 2 ? '=' : encoding_table[triple & 0x3F];
    }

    encoded_data[*output_length] = '\0';
    return encoded_data;
}

void upload_image(const char *image_name) {
    size_t image_size;
    unsigned char *image_bytes = read_image_to_bytes(image_name, &image_size);

    if (image_bytes == NULL) {
        printf("Failed to read the image file: %s\n", image_name);
        return;
    }

    size_t encoded_length;
    char *base64_string = convert_to_base64(image_bytes, image_size, &encoded_length);

    if (base64_string != NULL) {
        printf("Image Name: %s\nBase64 String:\n%s\n", image_name, base64_string);
    } else {
        printf("Failed to encode the image file to base64.\n");
    }

    free(image_bytes);
    free(base64_string);
}

int main() {
    const char *image_path = "path/to/your/image.jpg";
    upload_image(image_path);

#ifdef _WIN32
    Sleep(1000); // Wait for 1 second on Windows.
#else
    sleep(1); // Wait for 1 second on Unix-like systems.
#endif

    return 0;
}