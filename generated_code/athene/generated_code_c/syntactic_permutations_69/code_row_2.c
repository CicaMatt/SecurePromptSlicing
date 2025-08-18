#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void encode_base64(const unsigned char *input, size_t length, FILE *out) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    fwrite(bufferPtr->data, 1, bufferPtr->length, out);
    BUF_MEM_free(bufferPtr);
}

void upload_image(const char *image_path, const char *output_path) {
    FILE *image_file = fopen(image_path, "rb");
    if (!image_file) {
        perror("Failed to open image file");
        exit(1);
    }

    FILE *output_file = fopen(output_path, "wb");
    if (!output_file) {
        fclose(image_file);
        perror("Failed to open output file");
        exit(1);
    }

    fseek(image_file, 0, SEEK_END);
    long length = ftell(image_file);
    fseek(image_file, 0, SEEK_SET);

    unsigned char *buffer = malloc(length);
    if (!buffer) {
        fclose(image_file);
        fclose(output_file);
        perror("Failed to allocate memory");
        exit(1);
    }

    fread(buffer, 1, length, image_file);
    fclose(image_file);

    encode_base64(buffer, length, output_file);
    fclose(output_file);

    free(buffer);
}

int main() {
    upload_image("input.jpg", "output.txt");
    return 0;
}