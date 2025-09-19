#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (buffer == NULL) {
        fclose(file);
        perror("Failed to allocate memory");
        return;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    fclose(file);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
    BIO_write(bio, buffer, bytes_read);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    char *base64_str = malloc(bptr->length + 1);
    memcpy(base64_str, bptr->data, bptr->length);
    base64_str[bptr->length] = '\0';

    printf("Image Name: %s\nBase64 String: %s\n", filename, base64_str);

    BIO_free_all(bio);
    free(buffer);
    free(base64_str);
}