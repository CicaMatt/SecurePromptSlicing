#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *image_path, const char *image_name) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open image file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size);
    if (fread(buffer, 1, file_size, file) != (size_t)file_size) {
        perror("Failed to read image file");
        fclose(file);
        free(buffer);
        return;
    }
    fclose(file);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
    BIO_write(bio, buffer, file_size);
    BUF_MEM *bptr;
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bptr);
    BIO_set_close(bio, BIO_NOCLOSE); //So BIO_free_all doesn't free the buffer
    char *base64 = malloc(bptr->length + 1);
    memcpy(base64, bptr->data, bptr->length);
    base64[bptr->length] = '\0';

    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        free(buffer);
        free(base64);
        BIO_free_all(bio);
        return;
    }

    const char *sql = "INSERT INTO images (name, base64_data) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(buffer);
        free(base64);
        BIO_free_all(bio);
        return;
    }

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, base64, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    free(buffer);
    free(base64);
    BIO_free_all(bio);
}