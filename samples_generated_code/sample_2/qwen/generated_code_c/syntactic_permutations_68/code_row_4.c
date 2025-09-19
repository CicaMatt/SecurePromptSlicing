#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define DATABASE "images.db"
#define IMAGE_PATH "image.png"

void handle_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

char* base64_encode(const unsigned char *data, int length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // No newlines
    BIO_write(bio, data, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char *base64Encoded = (char *)malloc(bufferPtr->length + 1);
    memcpy(base64Encoded, bufferPtr->data, bufferPtr->length);
    base64Encoded[bufferPtr->length] = '\0';

    BIO_free_all(bio);

    return base64Encoded;
}

void upload_image() {
    FILE *imageFile = fopen(IMAGE_PATH, "rb");
    if (!imageFile) handle_error("Failed to open image file.");

    fseek(imageFile, 0, SEEK_END);
    long imageSize = ftell(imageFile);
    rewind(imageFile);

    unsigned char *imageData = (unsigned char *)malloc(imageSize + 1);
    fread(imageData, sizeof(unsigned char), imageSize, imageFile);
    fclose(imageFile);

    char *base64Image = base64_encode(imageData, imageSize);

    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db)) {
        handle_error("Failed to open database.");
    }

    char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        handle_error("Failed to prepare statement.");
    }

    sqlite3_bind_text(stmt, 1, IMAGE_PATH, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64Image, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        handle_error("Failed to execute statement.");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    free(imageData);
    free(base64Image);
}

int main() {
    upload_image();
    return 0;
}