#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *inputFilePath, const char *outputFilePath) {
    FILE *file = fopen(inputFilePath, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(fileSize);
    if (fread(buffer, 1, fileSize, file) != (size_t)fileSize) {
        perror("Error reading file");
        fclose(file);
        free(buffer);
        exit(EXIT_FAILURE);
    }
    fclose(file);

    BIO *bio, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line

    BIO_write(bio, buffer, fileSize);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bptr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    FILE *outFile = fopen(outputFilePath, "w");
    if (!outFile) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
    fwrite(bptr->data, 1, bptr->length, outFile);
    fclose(outFile);

    BUF_MEM_free(bptr);
    free(buffer);
}

int main() {
    upload_image("input.png", "encoded.txt");
    return 0;
}