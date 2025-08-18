#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void encode_base64(const unsigned char *input, size_t length, char **output) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    *output = BUF_MEM_data(bufferPtr);
    BUF_MEM_free(bufferPtr);
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("File opening failed");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(length);
    if (fread(buffer, 1, length, file) != length) {
        perror("File reading failed");
        fclose(file);
        free(buffer);
        return;
    }
    fclose(file);

    char *encoded;
    encode_base64(buffer, length, &encoded);

    FILE *output = fopen("encoded_image.txt", "w");
    if (!output) {
        perror("Output file opening failed");
        free(buffer);
        free(encoded);
        return;
    }

    fprintf(output, "%s", encoded);
    fclose(output);

    free(buffer);
    free(encoded);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    upload_image(argv[1]);
    return 0;
}