#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#define BASE64_ENCODED_SIZE(n) (((n) + 2 - ((n) % 3)) / 3 * 4)

char* base64_encode(const unsigned char *input, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
    BIO_write(bio, input, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    char *buff = (char *)malloc(bufferPtr->length + 1);
    memcpy(buff, bufferPtr->data, bufferPtr->length);
    buff[bufferPtr->length] = '\0';
    BUF_MEM_free(bufferPtr);

    return buff;
}

int upload_image(sqlite3 *db, const char *image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open image file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(length);
    if (fread(buffer, 1, length, file) != (size_t)length) {
        fclose(file);
        free(buffer);
        return -1;
    }
    fclose(file);

    char *base64_image = base64_encode(buffer, length);
    free(buffer);

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        free(base64_image);
        return -1;
    }

    const char *image_name = strrchr(image_path, '/');
    image_name = (image_name ? image_name + 1 : image_path);

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, base64_image, -1, SQLITE_TRANSIENT);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    free(base64_image);

    return (result == SQLITE_DONE) ? 0 : -1;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("images.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Database error: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT);";
    if (sqlite3_exec(db, create_table_sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    const char *image_path = "example.jpg";
    if (upload_image(db, image_path) == 0) {
        printf("Image uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload image.\n");
    }

    sqlite3_close(db);
    return 0;
}