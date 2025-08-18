#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define DATABASE "image.db"
#define BUFFER_SIZE 1024

void handle_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

char* image_to_base64(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) handle_error("Failed to open file");

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(length + 1);
    if (!buffer) handle_error("Memory allocation failed");
    fread(buffer, 1, length, file);
    fclose(file);

    BIO* bio, *b64;
    BUF_MEM* bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // No new line
    BIO_write(bio, buffer, length);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    char *base64Encoded = (char *)malloc(bufferPtr->length + 1);
    memcpy(base64Encoded, bufferPtr->data, bufferPtr->length);
    base64Encoded[bufferPtr->length] = '\0';

    BIO_free_all(bio);
    free(buffer);

    return base64Encoded;
}

void upload_image(const char* filename) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) handle_error("Cannot open database");

    const char* create_table_sql =
        "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "base64_data TEXT NOT NULL"
        ");";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) handle_error("Failed to create table");

    char* base64_string = image_to_base64(filename);

    char sql[512];
    snprintf(sql, sizeof(sql),
             "INSERT INTO images (name, base64_data) VALUES ('%s', '%s');",
             filename, base64_string);

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) handle_error("Failed to insert data");

    sqlite3_close(db);
    free(base64_string);
}

int main() {
    const char* image_filename = "example.jpg";
    upload_image(image_filename);
    return 0;
}