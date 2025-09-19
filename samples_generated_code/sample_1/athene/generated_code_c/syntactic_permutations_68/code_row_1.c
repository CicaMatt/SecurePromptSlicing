#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size);
    if (fread(buffer, 1, file_size, file) != (size_t)file_size) {
        perror("Failed to read file");
        fclose(file);
        free(buffer);
        return;
    }
    fclose(file);

    BIO *bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Do not add newlines to encoded output
    BIO *bmem = BIO_new(BIO_s_mem());
    bio = BIO_push(bio, bmem);
    
    BIO_write(bio, buffer, file_size);
    BIO_flush(bio);

    char *base64_str;
    long base64_len = BIO_get_mem_data(bmem, &base64_str);
    if (base64_len <= 0) {
        perror("Failed to encode image");
        BIO_free_all(bio);
        free(buffer);
        return;
    }

    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        BIO_free_all(bio);
        free(buffer);
        return;
    }

    char *sql = "INSERT INTO images (name, base64_data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        BIO_free_all(bio);
        free(buffer);
        return;
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_str, base64_len, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    BIO_free_all(bio);
    free(buffer);
}