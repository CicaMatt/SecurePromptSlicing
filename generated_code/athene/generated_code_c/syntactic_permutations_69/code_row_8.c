#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "rb");
    if (!in) {
        perror("Error opening input file");
        exit(1);
    }

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new_fp(stdout, BIO_NOCLOSE);
    bio = BIO_push(b64, bio);

    FILE *out = fopen(output_file, "w");
    if (!out) {
        perror("Error opening output file");
        fclose(in);
        exit(1);
    }

    char buffer[512];
    int len;
    while ((len = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        BIO_write(bio, buffer, len);
        BIO_flush(bio);
        BIO_gets(b64, buffer, sizeof(buffer));
        fwrite(buffer, 1, strlen(buffer), out);
    }

    fclose(in);
    fclose(out);
    BIO_free_all(bio);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    upload_image(argv[1], argv[2]);
    return 0;
}