#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define DATABASE "images.db"

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

char* image_to_base64(const unsigned char *data, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // ignore newlines
    BIO_write(bio, data, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    char *base64Encoded = (char *)malloc(bufferPtr->length + 1);
    memcpy(base64Encoded, bufferPtr->data, bufferPtr->length);
    base64Encoded[bufferPtr->length] = '\0';

    return base64Encoded;
}

void upload_image(const char* filename, const char* name) {
    FILE *file = fopen(filename, "rb");
    if (!file) handle_error("Failed to open file");

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(length);
    fread(buffer, 1, length, file);
    fclose(file);

    char *base64String = image_to_base64(buffer, length);
    free(buffer);

    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db) != SQLITE_OK) {
        handle_error("Failed to open database");
    }

    char *sql = "INSERT INTO images(name, data) VALUES(?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        handle_error("Failed to prepare statement");
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64String, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        handle_error("Failed to execute statement");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(base64String);
}

int main() {
    const char* filename = "example.jpg";
    const char* name = "Example Image";

    upload_image(filename, name);

    return 0;
}