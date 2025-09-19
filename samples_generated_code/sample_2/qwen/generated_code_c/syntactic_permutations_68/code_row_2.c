#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int base64_encode(const unsigned char *buffer, size_t length, char **b64text) {
    BIO *bio, *b64;
    int decode_length = 4*ceil((double)length/3), encode_length = 0;
    *b64text=(char *)malloc(decode_length+1);
    (*b64text)[decode_length] = '\0';
    bio = BIO_new_mem_buf(buffer, length);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    encode_length = BIO_read(bio, *b64text, decode_length);
    if(encode_length < 0) {
        handleErrors();
    }

    (*b64text)[encode_length] = '\0';

    BIO_free_all(bio);

    return encode_length;
}

void upload_image(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(length + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, length, file);
    fclose(file);

    char *base64;
    base64_encode(buffer, length, &base64);

    printf("Image Name: %s\n", filename);
    printf("Base64 String: %s\n", base64);

    free(base64);
    free(buffer);
}

int main() {
    upload_image("example.jpg");
    return 0;
}