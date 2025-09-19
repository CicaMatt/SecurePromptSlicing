#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void handle_sqlite_error(sqlite3 *db, int rc) {
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
}

char* to_base64(const unsigned char* input, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
    BIO_write(bio, input, length);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    char* base64 = (char*)malloc(bptr->length + 1); // Null terminator
    memcpy(base64, bptr->data, bptr->length);
    base64[bptr->length] = '\0';

    BIO_free_all(bio);

    return base64;
}

void upload_image(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    fclose(file);

    char *base64_data = to_base64(buffer, fsize);
    free(buffer);

    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    handle_sqlite_error(db, rc);

    const char* sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    handle_sqlite_error(db, rc);

    rc = sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_TRANSIENT);
    handle_sqlite_error(db, rc);

    rc = sqlite3_bind_text(stmt, 2, base64_data, -1, SQLITE_TRANSIENT);
    handle_sqlite_error(db, rc);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        free(base64_data);
        exit(1);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(base64_data);
}