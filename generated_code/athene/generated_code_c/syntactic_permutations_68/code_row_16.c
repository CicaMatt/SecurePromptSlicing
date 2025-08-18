#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(fsize + 1);
    if (fread(buffer, fsize, 1, file) != 1) {
        fclose(file);
        free(buffer);
        perror("Failed to read file");
        exit(EXIT_FAILURE);
    }
    buffer[fsize] = '\0';
    fclose(file);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Ignore newlines
    BIO_write(bio, buffer, fsize);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    char *base64 = malloc(bptr->length + 1);
    memcpy(base64, bptr->data, bptr->length);
    base64[bptr->length] = '\0';

    printf("Image Name: %s\n", filename);
    printf("Base64 String: %s\n", base64);

    BIO_free_all(bio);
    free(buffer);
    free(base64);
}