#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BASE64_ENCODE_OUT_SIZE (4 * ((size_t)(len) + 2) / 3)
#define BASE64_ENCODE_IN_SIZE (3 * ((size_t)(len) + 3) / 4)

char* base64_encode(const unsigned char *input, size_t length, size_t *out_len) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
    BIO_write(bio, input, length);
    BIO_flush(bio);
    BUF_MEM *buffer;
    BIO_get_mem_ptr(bio, &buffer);
    char *base64 = (char *)malloc(BASE64_ENCODE_OUT_SIZE + 1);
    if(base64 == NULL) {
        BIO_free_all(bio);
        return NULL;
    }
    memcpy(base64, buffer->data, buffer->length);
    base64[buffer->length] = '\0';

    *out_len = buffer->length;

    BIO_free_all(bio);
    BUF_MEM_free(buffer);

    return base64;
}

int upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return -1; // Error opening file
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *image_data = malloc(fsize + 1);
    fread(image_data, 1, fsize, file);
    fclose(file);

    size_t base64_len;
    char *base64_image = base64_encode(image_data, fsize, &base64_len);
    if (base64_image == NULL) {
        free(image_data);
        return -2; // Base64 encoding error
    }

    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc != SQLITE_OK) {
        free(base64_image);
        free(image_data);
        return -3; // Database open error
    }

    char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        free(base64_image);
        free(image_data);
        return -4; // SQL prepare error
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_image, base64_len, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        free(base64_image);
        free(image_data);
        return -5; // SQL execution error
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    free(base64_image);
    free(image_data);

    return 0;
}