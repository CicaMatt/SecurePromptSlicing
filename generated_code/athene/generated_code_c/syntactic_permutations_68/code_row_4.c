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
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    fclose(file);

    BIO *bio, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, buffer, fsize);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bptr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    char *base64 = malloc(bptr->length + 1);
    memcpy(base64, bptr->data, bptr->length);
    base64[bptr->length] = '\0';

    BUF_MEM_free(bptr);
    free(buffer);
    return base64;
}

int upload_image(sqlite3 *db, const char *filename) {
    char *base64_str = file_to_base64(filename);
    if (!base64_str) return -1;

    char sql[500];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s')", filename, base64_str);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        free(base64_str);
        return -1;
    }

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    free(base64_str);

    return (rc == SQLITE_DONE) ? 0 : -1;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT)";
    rc = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *filename = "example.jpg";
    int result = upload_image(db, filename);

    if (result == 0) {
        printf("Image uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload image.\n");
    }

    sqlite3_close(db);
    return 0;
}