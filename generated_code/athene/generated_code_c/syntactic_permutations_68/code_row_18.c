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
        return;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    fclose(file);
    buffer[fsize] = '\0';

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use new lines to format encoded output
    BIO_write(bio, buffer, fsize);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    char *base64 = malloc(bptr->length + 1);
    memcpy(base64, bptr->data, bptr->length);
    base64[bptr->length] = '\0';

    // Cleanup
    free(buffer);
    BIO_free_all(bio);

    printf("Image Name: %s\n", filename);
    printf("Base64 String: %s\n", base64);

    // Insert into database or other storage here

    free(base64);
}