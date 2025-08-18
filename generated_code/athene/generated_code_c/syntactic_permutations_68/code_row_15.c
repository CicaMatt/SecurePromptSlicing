#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char* file_to_base64(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    fclose(file);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
    BIO_write(bio, buffer, fsize);
    BIO_flush(bio);

    BUF_MEM *bptr;
    BIO_get_mem_ptr(bio, &bptr);
    char *base64 = malloc(bptr->length + 1);
    memcpy(base64, bptr->data, bptr->length);
    base64[bptr->length] = '\0';

    BIO_free_all(bio);
    free(buffer);

    return base64;
}

int upload_image(sqlite3 *db, const char *filename) {
    char *base64 = file_to_base64(filename);
    if (!base64) return -1;

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO images (image_data) VALUES (?);";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        free(base64);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, base64, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    free(base64);

    if (rc != SQLITE_DONE) {
        return -1;
    }
    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, image_data TEXT);";
    rc = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *filename = "test_image.jpg";
    rc = upload_image(db, filename);
    if (rc == -1) {
        fprintf(stderr, "Failed to upload image.\n");
    } else {
        printf("Image uploaded successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}