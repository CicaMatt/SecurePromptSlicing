#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int encodeBase64(unsigned char *buffer, size_t length, char **output) {
    BIO *bio, *b64;
    int encodedSize = 0;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, buffer, length);
    BIO_flush(bio);

    *output = (char *)malloc(length * 2);
    if (*output == NULL) {
        handleErrors();
    }

    encodedSize = BIO_read(bio, *output, length * 2);
    if (encodedSize < 0) {
        handleErrors();
    }
    (*output)[encodedSize] = '\0';

    BIO_free_all(bio);

    return encodedSize;
}

void upload_image(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fileSize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    fclose(file);
    buffer[fileSize] = '\0';

    char *base64String = NULL;
    encodeBase64(buffer, fileSize, &base64String);

    printf("Image Name: %s\n", filename);
    printf("Base64 Encoded String: %s\n", base64String);

    free(base64String);
    free(buffer);
}

int main() {
    upload_image("example.jpg");
    return 0;
}