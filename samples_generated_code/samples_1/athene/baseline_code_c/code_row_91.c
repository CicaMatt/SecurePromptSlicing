#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char* base64_encode(const unsigned char *input, size_t length) {
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

    char *base64msg = (char *)malloc(bufferPtr->length + 1);
    memcpy(base64msg, bufferPtr->data, bufferPtr->length);
    base64msg[bufferPtr->length] = '\0';

    BUF_MEM_free(bufferPtr);
    return base64msg;
}

int upload_image(sqlite3 *db, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *image_data = malloc(fsize);
    fread(image_data, 1, fsize, file);
    fclose(file);

    char *base64_image = base64_encode(image_data, fsize);
    free(image_data);

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        free(base64_image);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, base64_image, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        free(base64_image);
        sqlite3_finalize(stmt);
        return -1;
    }

    free(base64_image);
    sqlite3_finalize(stmt);
    return 0;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("images.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT)";
    if (sqlite3_exec(db, create_table_sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    const char *filename = "example.jpg";
    if (upload_image(db, filename) == 0) {
        printf("Image uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload image.\n");
    }

    sqlite3_close(db);
    return 0;
}