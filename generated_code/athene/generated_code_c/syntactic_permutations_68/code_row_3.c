#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BASE64_ENCODE_OUT_SIZE (4 * ((n + 2) / 3))

char* base64_encode(const unsigned char* data, int input_length, size_t* output_length) {
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
    char* base64_message = (char*)malloc(buffer->length + 1);
    memcpy(base64_message, buffer->data, buffer->length);
    base64_message[buffer->length] = '\0';

    BIO_free_all(bio);
    BUF_MEM_free(buffer);

    *output_length = buffer->length;
    return base64_message;
}

int upload_image(sqlite3* db, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return -1;

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* image_data = malloc(fsize);
    fread(image_data, 1, fsize, file);
    fclose(file);

    size_t base64_len;
    char* base64_image = base64_encode(image_data, (int)fsize, &base64_len);

    const char* sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        free(image_data);
        free(base64_image);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_image, (int)base64_len, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        free(image_data);
        free(base64_image);
        return -1;
    }

    sqlite3_finalize(stmt);
    free(image_data);
    free(base64_image);
    return 0;
}

int main() {
    sqlite3* db;
    int rc = sqlite3_open("images.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT);";
    rc = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    const char* filename = "example.jpg";
    rc = upload_image(db, filename);

    if (rc == 0) {
        printf("Image uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload image.\n");
    }

    sqlite3_close(db);
    return 0;
}