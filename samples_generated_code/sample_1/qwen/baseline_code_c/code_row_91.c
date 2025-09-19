#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define DATABASE "images.db"

void handle_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

char* image_to_base64(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        handle_error("Failed to open file");
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *file_buffer = (unsigned char *)malloc(fsize + 1);
    fread(file_buffer, fsize, 1, file);
    fclose(file);

    BIO *bio, *b64;
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, file_buffer, fsize);
    BIO_flush(bio);

    char *bufferPointer;
    long encodedSize = BIO_get_mem_data(bio, &bufferPointer);
    char *base64Text = (char *)malloc(encodedSize + 1);
    memcpy(base64Text, bufferPointer, encodedSize);
    base64Text[encodedSize] = '\0';

    BIO_free_all(bio);
    free(file_buffer);

    return base64Text;
}

int insert_image_to_db(sqlite3 *db, const char* image_name, const char* base64_string) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        handle_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_string, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        handle_error(sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc;
}

void create_table_if_not_exists(sqlite3 *db) {
    const char* sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY, name TEXT, data TEXT);";
    int rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        handle_error(sqlite3_errmsg(db));
    }
}

void upload_image(const char* filename) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        handle_error(sqlite3_errmsg(db));
    }

    create_table_if_not_exists(db);

    char* base64_string = image_to_base64(filename);
    insert_image_to_db(db, filename, base64_string);

    sqlite3_close(db);
    free(base64_string);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_image(argv[1]);

    return EXIT_SUCCESS;
}