#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void encodeBase64(FILE* infile, FILE* outfile);
int getFileSize(FILE *fp);

const unsigned char b64_chars[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

void encodeBase64(FILE* infile, FILE* outfile) {
    unsigned char buffer[3];
    unsigned char encoded[4];
    int bytesRead;

    while ((bytesRead = fread(buffer, 1, 3, infile)) > 0) {
        // Encode the three bytes read into four base64 characters
        encoded[0] = b64_chars[(buffer[0] & 0xFC) >> 2];
        encoded[1] = b64_chars[((buffer[0] & 0x03) << 4) | ((buffer[1] & 0xF0) >> 4)];
        encoded[2] = bytesRead > 1 ? b64_chars[((buffer[1] & 0x0F) << 2) | ((buffer[2] & 0xC0) >> 6)] : '=';
        encoded[3] = bytesRead > 2 ? b64_chars[buffer[2] & 0x3F] : '=';

        fwrite(encoded, sizeof(char), 4, outfile);
    }
}

int getFileSize(FILE *fp) {
    int size;
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    return size;
}

void upload_image(const char* input_filename, const char* output_filename) {
    FILE *infile = fopen(input_filename, "rb");
    if (!infile) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    int size = getFileSize(infile);

    // Open the base64 encoded file
    FILE *outfile = fopen(output_filename, "wb");
    if (!outfile) {
        fclose(infile);
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    encodeBase64(infile, outfile);

    fclose(infile);
    fclose(outfile);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_image_file> <output_base64_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_image(argv[1], argv[2]);

    return EXIT_SUCCESS;
}