#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define DATABASE "images.db"
#define IMAGE_TABLE "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, base64 BLOB);"

void upload_image(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = malloc(length);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, length, file);
    fclose(file);

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, buffer, length);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    char* base64String = malloc(bufferPtr->length + 1);
    memcpy(base64String, bufferPtr->data, bufferPtr->length);
    base64String[bufferPtr->length] = '\0';

    BIO_free_all(bio);
    free(buffer);

    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        free(base64String);
        return;
    }

    char* err_message = 0;
    const char* sql_create_table = IMAGE_TABLE;
    sqlite3_exec(db, sql_create_table, 0, 0, &err_message);

    char* sql_insert_image = "INSERT INTO images (name, base64) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql_insert_image, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(base64String);
        return;
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, base64String, bufferPtr->length, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(base64String);
}

int main() {
    upload_image("example.jpg");
    return 0;
}