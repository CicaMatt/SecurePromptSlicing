#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BASE64_ENCODE_LENGTH(n) ((((n) + 2) / 3) * 4)

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
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

    char *buff = (char *)malloc(BASE64_ENCODE_LENGTH(length) + 1);
    memcpy(buff, bufferPtr->data, bufferPtr->length);
    buff[bufferPtr->length] = '\0';
    BUF_MEM_free(bufferPtr);

    return buff;
}

void upload_image(const char *image_path, const char *image_name) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("File opening failed");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    fclose(file);

    char *base64_string = base64_encode(buffer, file_size);
    free(buffer);

    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s');", image_name, base64_string);
    free(base64_string);

    rc = sqlite3_exec(db, sql, callback, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);
}