#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

void error_exit(const char *msg) {
    perror(msg);
    exit(1);
}

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

    char *base64 = (char*)malloc(bufferPtr->length + 1); // Don't forget to free() this!
    memcpy(base64, bufferPtr->data, bufferPtr->length);
    base64[bufferPtr->length] = '\0';

    BUF_MEM_free(bufferPtr);

    return base64;
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) error_exit("Failed to open file");

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    unsigned char *image_data = malloc(fsize);
    fread(image_data, 1, fsize, file);
    fclose(file);

    char *base64_image = base64_encode(image_data, fsize);

    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc) error_exit("Can't open database");

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) error_exit("Failed to prepare statement");

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_image, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) error_exit("Failed to insert data into database");

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    free(image_data);
    free(base64_image);
}

int main() {
    upload_image("test.jpg");
    return 0;
}