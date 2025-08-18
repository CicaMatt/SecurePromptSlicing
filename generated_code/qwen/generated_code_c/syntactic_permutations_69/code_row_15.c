#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int base64_encode(const unsigned char* buffer, size_t length, char** b64text) {
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
    BIO_free_all(bio);

    *b64text = malloc(bufferPtr->length + 1);
    if (*b64text == NULL) return -1;
    memcpy(*b64text, bufferPtr->data, bufferPtr->length);
    (*b64text)[bufferPtr->length] = '\0';

    return 0;
}

void upload_image(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(fileSize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        perror("Failed to read file");
        free(buffer);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char *b64text;
    if (base64_encode(buffer, fileSize, &b64text) < 0) {
        perror("Base64 encoding failed");
        free(buffer);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    free(buffer);

    FILE *outputFile = fopen("encoded_image.txt", "w");
    if (!outputFile) {
        perror("Failed to open output file");
        free(b64text);
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "%s", b64text);
    fclose(outputFile);
    free(b64text);
}

int main() {
    upload_image("input_image.jpg");
    return 0;
}