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
    int encoded_size = 0;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    encoded_size = BIO_write(bio, buffer, length);
    if (BIO_flush(bio) != 1) handleErrors();

    *b64text = (char *)malloc(encoded_size + 1);
    (*b64text)[encoded_size] = '\0';

    BIO_get_mem_ptr(bio, &((BIO_MEM*)bio->ptr)->buf);

    memcpy(*b64text, ((BIO_MEM*)bio->ptr)->buffer->data,
           ((BIO_MEM*)bio->ptr)->buffer->length);

    BIO_free_all(bio);

    return encoded_size;
}

void upload_image(const char* filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0L, SEEK_END);
    size_t file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    if (fread(buffer, 1, file_size, fp) != file_size) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    char* base64_string;
    int encoded_length = base64_encode(buffer, file_size, &base64_string);

    FILE *output_file = fopen("encoded_image.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    fwrite(base64_string, 1, encoded_length, output_file);
    fclose(output_file);

    free(buffer);
    free(base64_string);
}

int main() {
    upload_image("image.jpg"); // Replace with your image file
    return 0;
}