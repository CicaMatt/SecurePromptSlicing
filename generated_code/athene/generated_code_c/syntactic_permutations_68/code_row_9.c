#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void upload_image(const char *filename, sqlite3 *db) {
    FILE *file = fopen(filename, "rb");
    if (!file) return;

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    unsigned char *image_data = malloc(fsize + 1);
    fread(image_data, 1, fsize, file);
    fclose(file);
    image_data[fsize] = '\0';

    BIO *bio = BIO_new(BIO_f_base64());
    BIO *bmem = BIO_new(BIO_s_mem());
    bio = BIO_push(bio, bmem);

    BIO_write(bio, image_data, fsize);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    char *base64_image = malloc(bptr->length + 1);
    memcpy(base64_image, bptr->data, bptr->length);
    base64_image[bptr->length] = '\0';

    BIO_free_all(bio);
    free(image_data);

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_image, -1, free);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT);";
    rc = sqlite3_exec(db, sql_create_table, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    upload_image("example.jpg", db);

    sqlite3_close(db);
    return 0;
}