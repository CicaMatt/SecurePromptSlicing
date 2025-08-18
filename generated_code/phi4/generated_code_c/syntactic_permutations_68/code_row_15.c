#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <mysql/mysql.h>
#include <libpq-fe.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <jpeglib.h>

#define BASE64_LENGTH(n) (((n + 2) / 3) * 4)

void handle_error(const char *message, const char *error_info) {
    fprintf(stderr, "%s: %s\n", message, error_info);
    exit(EXIT_FAILURE);
}

char* image_to_base64(unsigned char *image_data, size_t data_size) {
    BIO *bio_mem, *bio_b64;
    BUF_MEM *bptr;
    static char buffer[8192];

    bio_mem = BIO_new(BIO_s_mem());
    if (!bio_mem)
        handle_error("Failed to create memory BIO", NULL);

    bio_b64 = BIO_new(BIO_f_base64());
    if (!bio_b64) {
        BIO_free(bio_mem);
        handle_error("Failed to create base64 BIO", NULL);
    }

    bio_b64 = BIO_push(bio_b64, bio_mem);
    if (BIO_write(bio_b64, image_data, data_size) <= 0)
        handle_error("Error writing to base64 BIO", NULL);

    BIO_flush(bio_b64);
    BIO_get_mem_ptr(bio_b64, &bptr);
    strncpy(buffer, bptr->data, bptr->length);

    buffer[bptr->length] = '\0';
    BIO_free_all(bio_b64);

    return buffer;
}

void upload_image(const char *image_path) {
    FILE *file;
    unsigned char buffer[4096];
    size_t bytes_read;

    file = fopen(image_path, "rb");
    if (!file)
        handle_error("Failed to open image file", NULL);

    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *image_data = malloc(file_size);
    if (!image_data)
        handle_error("Memory allocation failed", NULL);

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        memcpy(image_data + (file_size - ftell(file)), buffer, bytes_read);
    }

    fclose(file);

    char *base64_image = image_to_base64(image_data, file_size);
    printf("Base64 Image: %s\n", base64_image);

    // Database connection
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        handle_error("Database connection failed", mysql_error(conn));
    }

    char query[8192];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES ('%s')",
             base64_image);

    if (mysql_query(conn, query)) {
        handle_error("Failed to insert image data into database", mysql_error(conn));
    }

    printf("Image uploaded successfully.\n");

    mysql_close(conn);
    free(image_data);
}

int main() {
    upload_image("path_to_your_image.jpg");
    return 0;
}