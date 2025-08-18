#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Include a library for encoding/decoding Base64 if available.
#ifdef __linux__
#include <openssl/bio.h>
#include <openssl/evp.h>
#endif

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

unsigned char* read_image_to_memory(const char *filename, size_t *size) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(*size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, *size, file);
    fclose(file);
    return buffer;
}

char* base64_encode(const unsigned char *input, size_t length) {
#ifdef __linux__
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char *b64text = (char *)malloc(bufferPtr->length);
    memcpy(b64text, bufferPtr->data, bufferPtr->length - 1);
    b64text[bufferPtr->length - 1] = 0;

    BIO_free_all(bio);
    return b64text;
#else
    fprintf(stderr, "Base64 encoding not supported on this platform.\n");
    exit(EXIT_FAILURE);
#endif
}

void upload_image(const char *filename) {
    size_t image_size;
    unsigned char *image_data = read_image_to_memory(filename, &image_size);

    char *base64_string = base64_encode(image_data, image_size);
    printf("Image Name: %s\n", filename);
    printf("Base64 String: %s\n", base64_string);

    free(image_data);
    free(base64_string);
}

int main(int argc, char **argv) {
#ifdef __linux__
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
#endif

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_image(argv[1]);

#ifdef __linux__
    // Clean up OpenSSL
    EVP_cleanup();
    ERR_free_strings();
#endif

    return EXIT_SUCCESS;
}