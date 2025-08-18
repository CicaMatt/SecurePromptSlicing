#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *filename, sqlite3 *db) {
    FILE *imageFile = fopen(filename, "rb");
    if (imageFile == NULL) return;

    fseek(imageFile, 0, SEEK_END);
    long fileSize = ftell(imageFile);
    rewind(imageFile);

    unsigned char *buffer = malloc(fileSize);
    fread(buffer, 1, fileSize, imageFile);
    fclose(imageFile);

    BIO *bio = BIO_new(BIO_f_base64());
    BIO *bmem = BIO_new(BIO_s_mem());
    bio = BIO_push(bio, bmem);
    BIO_write(bio, buffer, fileSize);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    char *base64 = malloc(bptr->length + 1);
    memcpy(base64, bptr->data, bptr->length);
    base64[bptr->length] = '\0';

    BIO_free_all(bio);
    free(buffer);

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64, -1, free);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Error inserting data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("images.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT);";
    if (sqlite3_exec(db, createTableSQL, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    upload_image("example.jpg", db);

    sqlite3_close(db);
    return 0;
}