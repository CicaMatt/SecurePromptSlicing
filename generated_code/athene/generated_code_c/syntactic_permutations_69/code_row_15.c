#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *inputFile, const char *outputFile) {
    FILE *file = fopen(inputFile, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(fileSize);
    if (fread(buffer, 1, fileSize, file) != (size_t)fileSize) {
        perror("Error reading file");
        fclose(file);
        free(buffer);
        return;
    }
    fclose(file);

    BIO *bio, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - don't add them
    BIO_write(bio, buffer, fileSize);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bptr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    FILE *outFile = fopen(outputFile, "w");
    if (outFile == NULL) {
        perror("Error opening output file");
        free(buffer);
        return;
    }

    fwrite(bptr->data, 1, bptr->length, outFile);
    fclose(outFile);

    BUF_MEM_free(bptr);
    free(buffer);
}

int main() {
    upload_image("image.jpg", "encoded.txt");
    return 0;
}