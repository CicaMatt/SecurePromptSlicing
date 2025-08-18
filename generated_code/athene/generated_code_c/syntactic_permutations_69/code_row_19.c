#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *image_path, const char *output_path) {
    FILE *image_file = fopen(image_path, "rb");
    if (!image_file) {
        perror("Failed to open image file");
        exit(EXIT_FAILURE);
    }

    fseek(image_file, 0, SEEK_END);
    long file_size = ftell(image_file);
    fseek(image_file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(image_file);
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, image_file);
    fclose(image_file);

    BIO *bio = BIO_new(BIO_f_base64());
    BIO_push(bio, BIO_new(BIO_s_mem()));
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Do not add new lines to encoded output
    BIO_write(bio, buffer, file_size);
    BIO_flush(bio);

    BUF_MEM *bptr = NULL;
    BIO_get_mem_ptr(bio, &bptr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    FILE *output_file = fopen(output_path, "w");
    if (!output_file) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    fwrite(bptr->data, 1, bptr->length, output_file);
    fclose(output_file);
    BUF_MEM_free(bptr);

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_path> <output_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    upload_image(argv[1], argv[2]);
    return EXIT_SUCCESS;
}