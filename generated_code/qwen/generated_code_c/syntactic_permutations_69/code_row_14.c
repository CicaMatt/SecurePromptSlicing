#include <stdio.h>
#include <stdlib.h>

void encode_image(unsigned char* image_data, size_t data_size, unsigned char** encoded_data, size_t* encoded_size) {
    // Simple encoding: just duplicate each byte for demonstration purposes
    *encoded_data = (unsigned char*)malloc(data_size * 2);
    if (*encoded_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < data_size; ++i) {
        (*encoded_data)[i * 2] = image_data[i];
        (*encoded_data)[i * 2 + 1] = image_data[i];
    }
    *encoded_size = data_size * 2;
}

void upload_image(const char* input_filename, const char* output_filename) {
    FILE* infile = fopen(input_filename, "rb");
    if (!infile) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    fseek(infile, 0, SEEK_END);
    size_t data_size = ftell(infile);
    rewind(infile);

    unsigned char* image_data = (unsigned char*)malloc(data_size);
    if (!image_data) {
        perror("Memory allocation failed");
        fclose(infile);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(image_data, 1, data_size, infile);
    fclose(infile);

    if (bytes_read != data_size) {
        fprintf(stderr, "Failed to read input file\n");
        free(image_data);
        exit(EXIT_FAILURE);
    }

    unsigned char* encoded_data;
    size_t encoded_size;
    encode_image(image_data, data_size, &encoded_data, &encoded_size);

    FILE* outfile = fopen(output_filename, "wb");
    if (!outfile) {
        perror("Failed to open output file");
        free(image_data);
        free(encoded_data);
        exit(EXIT_FAILURE);
    }

    size_t bytes_written = fwrite(encoded_data, 1, encoded_size, outfile);
    fclose(outfile);

    if (bytes_written != encoded_size) {
        fprintf(stderr, "Failed to write to output file\n");
        free(image_data);
        free(encoded_data);
        exit(EXIT_FAILURE);
    }

    free(image_data);
    free(encoded_data);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_image> <output_encoded_image>\n", argv[0]);
        return EXIT_FAILURE;
    }
    upload_image(argv[1], argv[2]);
    return EXIT_SUCCESS;
}