#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *input_file, const char *output_file) {
    FILE *file = fopen(input_file, "rb");
    if (!file) {
        perror("Failed to open input file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    if (fread(buffer, 1, file_size, file) != (size_t)file_size) {
        perror("Failed to read input file");
        fclose(file);
        free(buffer);
        exit(1);
    }
    fclose(file);

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
    BIO_write(bio, buffer, file_size);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    FILE *out = fopen(output_file, "w");
    if (!out) {
        perror("Failed to open output file");
        free(buffer);
        exit(1);
    }

    fwrite(bufferPtr->data, 1, bufferPtr->length, out);
    fclose(out);
    BUF_MEM_free(bufferPtr);
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