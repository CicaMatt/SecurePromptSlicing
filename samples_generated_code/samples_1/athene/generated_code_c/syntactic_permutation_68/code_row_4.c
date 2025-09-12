#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *image_path, sqlite3 *db) {
    FILE *fp = fopen(image_path, "rb");
    if (!fp) {
        perror("Failed to open image file");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    unsigned char *image_data = malloc(file_size);
    if (fread(image_data, 1, file_size, fp) != file_size) {
        perror("Failed to read image file");
        free(image_data);
        fclose(fp);
        return;
    }
    fclose(fp);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); //Do not add new lines every 64 bytes
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, image_data, file_size);
    BIO_flush(bio);

    char *base64_str;
    long base64_len = BIO_get_mem_data(bio, &base64_str);

    char *image_name = strrchr(image_path, '/');
    if (image_name) {
        image_name++;
    } else {
        image_name = (char *)image_path;
    }

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_str, base64_len, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert image into database: %s\n", sqlite3_errmsg(db));
    }

    BIO_free_all(bio);
    free(image_data);
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("images.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT);";
    if (sqlite3_exec(db, create_table_sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    upload_image("path/to/image.jpg", db);

    sqlite3_close(db);
    return 0;
}