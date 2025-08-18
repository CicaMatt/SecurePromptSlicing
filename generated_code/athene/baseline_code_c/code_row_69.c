#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *input_file, const char *output_file) {
    FILE *file = fopen(input_file, "rb");
    if (!file) {
        perror("Failed to open image file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(file);
        perror("Failed to allocate memory for image buffer");
        exit(1);
    }

    size_t read_size = fread(buffer, 1, file_size, file);
    fclose(file);

    BIO *bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Don't add newlines to encoded output
    BIO *bmem = BIO_new(BIO_s_mem());
    bio = BIO_push(bio, bmem);

    BIO_write(bio, buffer, read_size);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    BIO_set_close(bio, BIO_NOCLOSE); // Don't free the attached memory when freeing the BIO
    BIO_free_all(bio);

    FILE *out_file = fopen(output_file, "w");
    if (!out_file) {
        perror("Failed to open output file");
        exit(1);
    }

    fwrite(bptr->data, 1, bptr->length, out_file);
    fclose(out_file);

    BUF_MEM_free(bptr);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_image> <output_file>\n", argv[0]);
        exit(1);
    }

    upload_image(argv[1], argv[2]);
    return 0;
}