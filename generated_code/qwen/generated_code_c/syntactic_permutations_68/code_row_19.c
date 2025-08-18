#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

char* encode_to_base64(unsigned char *data, int length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, data, length);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    char *base64Encoded = (char *)malloc(bufferPtr->length + 1);
    memcpy(base64Encoded, bufferPtr->data, bufferPtr->length);
    base64Encoded[bufferPtr->length] = '\0';

    BIO_free_all(bio);

    return base64Encoded;
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

    unsigned char *imageData = (unsigned char *)malloc(length + 1);
    fread(imageData, 1, length, file);
    fclose(file);

    imageData[length] = '\0';

    char* base64String = encode_to_base64(imageData, length);
    free(imageData);

    // Insert into database or send over network
    printf("Image Name: %s\n", filename);
    printf("Base64 String: %s\n", base64String);

    free(base64String);
}

int main() {
    upload_image("example.jpg");
    return 0;
}