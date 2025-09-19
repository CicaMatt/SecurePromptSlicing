#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char* read_file_to_base64(const char* filename, size_t *out_len) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    fclose(file);

    BIO *bio, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
    BIO_write(bio, buffer, file_size);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bptr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    char *base64_str = malloc(bptr->length + 1);
    memcpy(base64_str, bptr->data, bptr->length);
    base64_str[bptr->length] = '\0';

    BUF_MEM_free(bptr);
    free(buffer);

    if (out_len) {
        *out_len = bptr->length;
    }

    return base64_str;
}

int upload_image(const char* filename, sqlite3 *db) {
    size_t base64_len;
    char *base64_data = read_file_to_base64(filename, &base64_len);
    if (!base64_data) return -1;

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        free(base64_data);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, base64_data, base64_len, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    free(base64_data);

    return (rc == SQLITE_DONE) ? 0 : -1;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT)";
    rc = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't execute SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *filename = "example.jpg";
    rc = upload_image(filename, db);
    if (rc != 0) {
        fprintf(stderr, "Failed to upload image.\n");
    } else {
        printf("Image uploaded successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}