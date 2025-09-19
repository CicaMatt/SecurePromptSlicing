#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

void upload_image(const char *input_path, const char *output_path) {
    FILE *file = fopen(input_path, "rb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(file);
        perror("Error allocating memory");
        exit(1);
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio_out = BIO_new_file(output_path, "w");
    bio_out = BIO_push(b64, bio_out);

    BIO_set_flags(bio_out, BIO_FLAGS_BASE64_NO_NL); // Don't add newlines to encoded output
    BIO_write(bio_out, buffer, file_size);
    BIO_flush(bio_out);

    BIO_free_all(bio_out);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_image_path> <output_encoded_path>\n", argv[0]);
        return 1;
    }

    upload_image(argv[1], argv[2]);
    return 0;
}