#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

char* base64_encode(const unsigned char* input, size_t length) {
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
    char* base64 = (char*)malloc(buffer->length + 1);
    memcpy(base64, buffer->data, buffer->length);
    base64[buffer->length] = '\0';

    BIO_free_all(bio);

    return base64;
}

void upload_image(sqlite3 *db, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) handle_error("Failed to open file");

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    unsigned char *imageData = malloc(fileSize);
    if (fread(imageData, 1, fileSize, file) != fileSize) {
        fclose(file);
        free(imageData);
        handle_error("Failed to read file");
    }
    fclose(file);

    char *base64Image = base64_encode(imageData, fileSize);
    free(imageData);

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        handle_error("Failed to prepare statement");
    }

    if (sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, base64Image, -1, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        free(base64Image);
        handle_error("Failed to bind parameters");
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        free(base64Image);
        handle_error("Failed to execute statement");
    }

    sqlite3_finalize(stmt);
    free(base64Image);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("images.db", &db) != SQLITE_OK) {
        handle_error("Failed to open database");
    }

    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY, name TEXT, data TEXT);";
    if (sqlite3_exec(db, createTableSQL, NULL, NULL, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        handle_error("Failed to create table");
    }

    upload_image(db, "example.jpg");

    sqlite3_close(db);

    return 0;
}