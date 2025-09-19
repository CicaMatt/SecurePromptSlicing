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
    fseek(file, 0, SEEK_SET);

    unsigned char *image_data = malloc(fsize + 1);
    fread(image_data, 1, fsize, file);
    fclose(file);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not add newlines to encoded output
    BIO_write(bio, image_data, fsize);
    BIO_flush(bio);

    BUF_MEM *buffer_ptr;
    BIO_get_mem_ptr(bio, &buffer_ptr);
    BIO_set_close(bio, BIO_NOCLOSE); //So BIO_free_all doesn't free the buffer
    BIO_free_all(bio);

    char *base64_image = malloc(buffer_ptr->length + 1);
    memcpy(base64_image, buffer_ptr->data, buffer_ptr->length);
    base64_image[buffer_ptr->length] = '\0';

    printf("Image name: %s\n", filename);
    printf("Base64 string:\n%s\n", base64_image);

    free(image_data);
    free(base64_image);
    BUF_MEM_free(buffer_ptr);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image file>\n", argv[0]);
        return 1;
    }
    upload_image(argv[1]);
    return 0;
}