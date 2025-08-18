#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define DATABASE "images.db"

void handle_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

char* image_to_base64(const unsigned char *data, size_t input_length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // No new line
    BIO_write(bio, data, input_length);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    char *base64Encoded = (char *)malloc(bufferPtr->length + 1);
    memcpy(base64Encoded, bufferPtr->data, bufferPtr->length);
    base64Encoded[bufferPtr->length] = '\0';

    BIO_free_all(bio);

    return base64Encoded;
}

void upload_image(const char *image_path, const char *image_name) {
    FILE *file_ptr = fopen(image_path, "rb");
    if (!file_ptr) handle_error("Failed to open image file");

    fseek(file_ptr, 0L, SEEK_END);
    size_t image_size = ftell(file_ptr);
    rewind(file_ptr);

    unsigned char *image_data = (unsigned char *)malloc(image_size + 1);
    fread(image_data, sizeof(unsigned char), image_size, file_ptr);
    fclose(file_ptr);

    char *base64_image = image_to_base64(image_data, image_size);
    free(image_data);

    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db)) handle_error("Failed to open database");

    char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
        handle_error(sqlite3_errmsg(db));

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_image, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) handle_error(sqlite3_errmsg(db));

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    free(base64_image);
}

int main() {
    upload_image("path/to/image.jpg", "image_name.jpg");
    return 0;
}