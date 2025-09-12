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
    int encoded_size = 0;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // No newlines
    BIO_write(bio, buffer, length);
    BIO_flush(bio);

    *b64text = (char *)malloc(length * 2);
    encoded_size = BIO_read(bio, *b64text, length * 2);
    (*b64text)[encoded_size] = '\0';

    BIO_free_all(bio);

    return encoded_size;
}

void upload_image(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0L, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(filesize + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fread(buffer, sizeof(unsigned char), filesize, fp);
    fclose(fp);

    char *base64string;
    int base64length = base64_encode(buffer, filesize, &base64string);
    if (base64length < 0) {
        handleErrors();
    }

    // Insert image name and base64 string into the database or file
    printf("Image Name: %s\n", filename);
    printf("Base64 Encoded String:\n%s\n", base64string);

    free(base64string);
    free(buffer);
}

int main() {
    upload_image("example.jpg");
    return 0;
}