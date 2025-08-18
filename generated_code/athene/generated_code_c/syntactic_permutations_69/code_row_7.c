#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void encode_base64(const unsigned char *input, size_t length, FILE *output) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not add new line every 64 bytes

    BIO_write(bio, input, length);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    fwrite(bufferPtr->data, 1, bufferPtr->length, output);
    BUF_MEM_free(bufferPtr);
}

void upload_image(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "rb");
    if (!in) {
        perror("Error opening input file");
        return;
    }

    FILE *out = fopen(outputFile, "wb");
    if (!out) {
        fclose(in);
        perror("Error opening output file");
        return;
    }

    fseek(in, 0, SEEK_END);
    long size = ftell(in);
    fseek(in, 0, SEEK_SET);

    unsigned char *buffer = malloc(size);
    if (fread(buffer, 1, size, in) != size) {
        fclose(in);
        fclose(out);
        free(buffer);
        perror("Error reading input file");
        return;
    }

    encode_base64(buffer, size, out);

    free(buffer);
    fclose(in);
    fclose(out);
}