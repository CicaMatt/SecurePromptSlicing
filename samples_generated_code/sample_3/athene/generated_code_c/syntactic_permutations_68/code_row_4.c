#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

char* file_to_base64(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) handle_error("Failed to open file");

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *data = malloc(fsize + 1);
    if (fread(data, 1, fsize, file) != (size_t)fsize) handle_error("Failed to read file");
    fclose(file);

    BIO *bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Remove newlines from output
    BIO *bmem = BIO_new(BIO_s_mem());
    bio = BIO_push(bio, bmem);

    if (BIO_write(bio, data, fsize) <= 0) handle_error("Failed to write to BIO");
    if (BIO_flush(bio) <= 0) handle_error("Failed to flush BIO");

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    char *base64 = malloc(bptr->length + 1);
    memcpy(base64, bptr->data, bptr->length);
    base64[bptr->length] = '\0';

    BIO_free_all(bio);
    free(data);

    return base64;
}

void upload_image(sqlite3 *db, const char *filename) {
    char *base64_str = file_to_base64(filename);
    if (!base64_str) handle_error("Failed to convert image to base64");

    char sql[1024];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s')", filename, base64_str);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) handle_error("Failed to prepare statement");
    if (sqlite3_step(stmt) != SQLITE_DONE) handle_error("Failed to execute statement");

    sqlite3_finalize(stmt);
    free(base64_str);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("images.db", &db) != SQLITE_OK) handle_error("Failed to open database");

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY, name TEXT, data TEXT);";
    sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);

    upload_image(db, "example.jpg"); // Example image file

    sqlite3_close(db);
    return 0;
}