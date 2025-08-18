#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BASE64_ENCODE_RATIO (4.0 / 3.0)

static int insert_into_db(sqlite3 *db, const char *name, const char *base64) {
    char sql[1024];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s');", name, base64);
    char *err_msg = NULL;
    return sqlite3_exec(db, sql, NULL, NULL, &err_msg);
}

char* file_to_base64(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(length);
    if (fread(buffer, 1, length, file) != (size_t)length) {
        fclose(file);
        free(buffer);
        return NULL;
    }
    fclose(file);

    BIO *bio, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, buffer, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bptr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    char *base64 = malloc(BASE64_ENCODE_RATIO * length + 1);
    memcpy(base64, bptr->data, bptr->length);
    base64[bptr->length] = '\0';
    BUF_MEM_free(bptr);
    free(buffer);

    return base64;
}

void upload_image(const char *filename) {
    sqlite3 *db;
    if (sqlite3_open("images.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *base64 = file_to_base64(filename);
    if (!base64) {
        fprintf(stderr, "Failed to convert image to base64.\n");
        sqlite3_close(db);
        return;
    }

    const char *name = strrchr(filename, '/');
    name = (name ? name + 1 : filename);

    int rc = insert_into_db(db, name, base64);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to insert into database: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Image uploaded successfully.\n");
    }

    free(base64);
    sqlite3_close(db);
}