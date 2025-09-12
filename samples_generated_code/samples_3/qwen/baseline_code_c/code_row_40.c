#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

void handle_errors() {
    ERR_print_errors_fp(stderr);
    abort();
}

char* encode_base64(const unsigned char* buffer, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, buffer, length);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);

    char* base64Encoded = (char*)malloc(bufferPtr->length + 1);
    memcpy(base64Encoded, bufferPtr->data, bufferPtr->length);
    base64Encoded[bufferPtr->length] = '\0';

    BIO_free_all(bio);

    return base64Encoded;
}

void upload_image(const char* imagePath) {
    FILE *file = fopen(imagePath, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(fileSize + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, sizeof(unsigned char), fileSize, file);
    fclose(file);

    char* base64EncodedImage = encode_base64(buffer, fileSize);
    free(buffer);

    FILE *encodedFile = fopen("encoded_image.txt", "w");
    if (!encodedFile) {
        perror("Failed to open encoded image file for writing");
        free(base64EncodedImage);
        exit(EXIT_FAILURE);
    }

    fprintf(encodedFile, "%s\n", base64EncodedImage);
    fclose(encodedFile);

    free(base64EncodedImage);
}

int main() {
    upload_image("path_to_your_image.jpg");
    return 0;
}