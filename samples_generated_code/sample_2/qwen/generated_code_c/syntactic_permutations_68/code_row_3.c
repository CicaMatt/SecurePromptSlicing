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
    int decode_length = 4*ceil((double)length/3);
    *b64text=(char *)malloc(decode_length+1);
    (*b64text)[decode_length] = '\0';
    bio = BIO_new_mem_buf(buffer, length);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Do not write new lines to the buffer
    int encoded_length = BIO_read(bio, *b64text, decode_length);
    if(encoded_length < 0) {
        handleErrors();
    }

    BIO_free_all(bio);

    return encoded_length;
}

void upload_image(const char* image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(length);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, length, file);
    fclose(file);

    char *base64_string;
    base64_encode(buffer, length, &base64_string);

    // Insert image name and base64 string into database or another storage
    printf("Image Name: %s\n", image_path);
    printf("Base64 String: %s\n", base64_string);

    free(base64_string);
    free(buffer);
}

int main() {
    upload_image("path/to/image.jpg");
    return 0;
}
