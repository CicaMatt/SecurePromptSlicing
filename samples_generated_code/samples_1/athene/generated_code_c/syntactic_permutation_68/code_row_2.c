#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *image_path, char **base64_str) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open image file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (fread(buffer, 1, file_size, file) != file_size) {
        perror("Failed to read image file");
        fclose(file);
        free(buffer);
        exit(1);
    }
    fclose(file);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Remove newlines from base64 encoding

    BIO_write(bio, buffer, file_size);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    *base64_str = malloc(bptr->length + 1);
    memcpy(*base64_str, bptr->data, bptr->length);
    (*base64_str)[bptr->length] = '\0';

    BIO_free_all(bio);
    free(buffer);
}

int main() {
    char *image_name = "example.jpg";
    char *encoded_image;

    upload_image(image_name, &encoded_image);

    printf("Image Name: %s\n", image_name);
    printf("Base64 String: %s\n", encoded_image);

    free(encoded_image);
    return 0;
}