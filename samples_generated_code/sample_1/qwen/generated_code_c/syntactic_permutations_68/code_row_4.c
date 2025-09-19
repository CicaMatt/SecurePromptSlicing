#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define DATABASE "images.db"

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

char* image_to_base64(const char* filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) handle_error("Failed to open file");

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char *file_buffer = malloc(fsize + 1);
    if (!file_buffer) handle_error("Memory allocation failed");
    
    fread(file_buffer, fsize, 1, fp);
    fclose(fp);

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Ignore newlines - write everything in one line
    BIO_write(bio, file_buffer, fsize);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    char *base64Encoded = (char *)malloc(bufferPtr->length + 1);
    memcpy(base64Encoded, bufferPtr->data, bufferPtr->length);
    base64Encoded[bufferPtr->length] = '\0';

    BIO_free_all(bio);

    free(file_buffer);
    return base64Encoded;
}

void upload_image(const char* image_name, const char* filename) {
    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db)) handle_error("Failed to open database");

    char *sql = "CREATE TABLE IF NOT EXISTS images ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL,"
                "base64 BLOB NOT NULL);";
    char *err_message;
    if (sqlite3_exec(db, sql, 0, 0, &err_message) != SQLITE_OK) {
        sqlite3_free(err_message);
        handle_error("SQL error");
    }

    char *base64_string = image_to_base64(filename);

    sql = "INSERT INTO images (name, base64) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) handle_error("SQL error");

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_string, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) handle_error("SQL error");
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(base64_string);
}

int main() {
    upload_image("example.jpg", "path/to/example.jpg");
    return 0;
}