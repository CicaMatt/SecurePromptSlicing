#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BASE64_ENCODE_OUT_SIZE (4 * ((file_size + 2) / 3))

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

char* base64_encode(const unsigned char* input, size_t length, size_t* output_length) {
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

    char* base64message = (char*)malloc(bufferPtr->length + 1); // Don't forget null terminator
    memcpy(base64message, bufferPtr->data, bufferPtr->length);
    base64message[bufferPtr->length] = '\0';

    BUF_MEM_free(bufferPtr);

    *output_length = bufferPtr->length;
    return base64message;
}

void upload_image(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) handle_error("fopen");

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size + 1);
    if (!buffer) handle_error("malloc");

    fread(buffer, 1, file_size, file);
    fclose(file);

    size_t base64_length;
    char *base64_encoded = base64_encode(buffer, file_size, &base64_length);

    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc) handle_error("sqlite3_open");

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) handle_error("sqlite3_prepare_v2");

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, base64_encoded, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) handle_error("sqlite3_step");

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    free(buffer);
    free(base64_encoded);
}

int main() {
    // Example usage
    upload_image("example.png");
    return 0;
}