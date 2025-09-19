#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *image_path, const char *db_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open image file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *image_data = malloc(length);
    if (fread(image_data, 1, length, file) != (size_t)length) {
        perror("Failed to read image data");
        fclose(file);
        free(image_data);
        return;
    }
    fclose(file);

    BIO *bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Ignore newlines
    BIO *bmem = BIO_new(BIO_s_mem());
    bio = BIO_push(bio, bmem);

    BIO_write(bio, image_data, length);
    BIO_flush(bio);

    BUF_MEM *buffer_ptr;
    BIO_get_mem_ptr(bio, &buffer_ptr);
    char *base64_str = malloc(buffer_ptr->length + 1);
    memcpy(base64_str, buffer_ptr->data, buffer_ptr->length);
    base64_str[buffer_ptr->length] = '\0';

    BIO_free_all(bio);
    free(image_data);

    sqlite3 *db;
    if (sqlite3_open(db_path, &db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        free(base64_str);
        return;
    }

    char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(base64_str);
        return;
    }

    const char *image_name = strrchr(image_path, '/');
    if (image_name == NULL || image_name[1] == '\0') {
        image_name = image_path;
    } else {
        image_name++;
    }

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_str, -1, free);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}