#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *image_path, char **encoded_image, size_t *encoded_length) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open image file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    fread(buffer, 1, file_size, file);
    fclose(file);

    BIO *bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Remove newlines from encoded output
    BIO *bmem = BIO_new(BIO_s_mem());
    bio = BIO_push(bio, bmem);

    BIO_write(bio, buffer, file_size);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    *encoded_length = bptr->length;
    *encoded_image = malloc(*encoded_length + 1); // +1 for null terminator
    memcpy(*encoded_image, bptr->data, *encoded_length);
    (*encoded_image)[*encoded_length] = '\0';

    BIO_free_all(bio);
    free(buffer);
}