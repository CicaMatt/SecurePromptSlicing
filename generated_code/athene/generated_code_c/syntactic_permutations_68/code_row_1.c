#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BASE64_ENCODE_OUT_SIZE (4 * ((input_len + 2) / 3))
char* base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
    BIO_write(bio, data, input_length);
    BIO_flush(bio);
    BUF_MEM *buffer;
    BIO_get_mem_ptr(bio, &buffer);
    char *base64msg = (char *)malloc(buffer->length + 1);
    memcpy(base64msg, buffer->data, buffer->length);
    base64msg[buffer->length] = '\0';
    BIO_free_all(bio);
    BUF_MEM_free(buffer);

    if (output_length) {
        *output_length = buffer->length;
    }

    return base64msg;
}

int upload_image(sqlite3 *db, const char *image_name, const unsigned char *image_data, size_t image_size) {
    char *base64_image;
    size_t base64_len;

    base64_image = base64_encode(image_data, image_size, &base64_len);
    if (base64_image == NULL) {
        return -1; // Error encoding
    }

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        free(base64_image);
        return -2; // Error preparing statement
    }

    rc = sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        free(base64_image);
        return -3; // Error binding name
    }

    rc = sqlite3_bind_text(stmt, 2, base64_image, base64_len, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        free(base64_image);
        return -4; // Error binding data
    }

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    free(base64_image);

    if (rc != SQLITE_DONE) {
        return -5; // Error executing statement
    }

    return 0;
}

int main() {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT);";
    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        return -2;
    }

    // Example usage of upload_image
    const char *image_name = "example.jpg";
    unsigned char image_data[] = { /* ... image data here ... */ };
    size_t image_size = sizeof(image_data);

    rc = upload_image(db, image_name, image_data, image_size);
    if (rc != 0) {
        fprintf(stderr, "Failed to upload image: %d\n", rc);
    } else {
        printf("Image uploaded successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}