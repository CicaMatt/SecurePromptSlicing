#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include OpenSSL headers for base64 encoding
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BUFFER_SIZE 1024

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

char* encodeToBase64(const unsigned char *input, int length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Do not use newlines to flush buffer
    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);

    char *base64 = (char *)malloc(bufferPtr->length);
    memcpy(base64, bufferPtr->data, bufferPtr->length - 1); // Remove the trailing newline
    base64[bufferPtr->length - 1] = '\0';

    BIO_free_all(bio);

    return base64;
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(filesize + 1);
    fread(buffer, 1, filesize, file);
    fclose(file);

    buffer[filesize] = '\0'; // Null-terminate the buffer

    char *base64 = encodeToBase64(buffer, filesize);
    free(buffer);

    printf("Image Name: %s\n", filename);
    printf("Base64 String: %s\n", base64);

    // Insert into database or any other storage
    // For demonstration purposes, we'll just print the values

    // Free allocated memory for base64 string
    free(base64);
}

int main() {
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();

    const char *image_filename = "example.jpg";
    upload_image(image_filename);

    EVP_cleanup();
    return 0;
}