#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BUFFER_SIZE 4096

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int upload_image(sqlite3 *db, const char *image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Unable to open file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size);
    fread(buffer, 1, file_size, file);
    fclose(file);

    BIO *bio_mem = BIO_new_mem_buf(buffer, file_size);
    BIO *bio_base64 = BIO_new(BIO_f_base64());
    bio_base64 = BIO_push(bio_base64, bio_mem);

    BUF_MEM *buffer_ptr;
    BIO_get_mem_ptr(bio_base64, &buffer_ptr);
    BIO_set_close(bio_base64, BIO_NOCLOSE);

    unsigned char *base64_data = (unsigned char *)malloc(buffer_ptr->length + 1);
    memcpy(base64_data, buffer_ptr->data, buffer_ptr->length);
    base64_data[buffer_ptr->length] = '\0';

    BIO_free_all(bio_base64);
    free(buffer);

    const char *image_name = strrchr(image_path, '/') ? strrchr(image_path, '/') + 1 : image_path;

    sqlite3_stmt *stmt;
    const char *sql_insert = "INSERT INTO images (name, data) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        free(base64_data);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, base64_data, strlen((const char *)base64_data), SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        free(base64_data);
        return -1;
    }

    sqlite3_finalize(stmt);
    free(base64_data);

    printf("Image uploaded successfully.\n");
    return 0;
}

int main() {
    const char *db_filename = "images.db";
    sqlite3 *db;
    if (sqlite3_open(db_filename, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "data BLOB);";

    if (sqlite3_exec(db, sql_create_table, callback, 0, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    const char *image_path = "path_to_your_image.jpg";
    upload_image(db, image_path);

    sqlite3_close(db);
    return 0;
}