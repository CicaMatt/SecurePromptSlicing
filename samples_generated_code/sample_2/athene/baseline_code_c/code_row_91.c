#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char* file_to_base64(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *data = malloc(fsize + 1);
    fread(data, 1, fsize, file);
    fclose(file);
    data[fsize] = '\0';

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, data, fsize);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);
    BIO_free_all(bio);

    char *base64msg = (char *)malloc(bufferPtr->length + 1);
    memcpy(base64msg, bufferPtr->data, bufferPtr->length);
    base64msg[bufferPtr->length] = '\0';

    BUF_MEM_free(bufferPtr);
    free(data);

    return base64msg;
}

int upload_image(const char *filename) {
    sqlite3 *db;
    int rc;
    char *sql, *base64data;

    if (sqlite3_open("images.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    base64data = file_to_base64(filename);
    if (!base64data) {
        fprintf(stderr, "Failed to read and encode image.\n");
        sqlite3_close(db);
        return 1;
    }

    sql = sqlite3_mprintf("INSERT INTO images (name, data) VALUES ('%q', '%q');", filename, base64data);

    rc = sqlite3_exec(db, sql, NULL, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_free(sql);
        free(base64data);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_free(sql);
    free(base64data);
    sqlite3_close(db);

    return 0;
}

int main() {
    // Example usage
    upload_image("example.jpg");
    return 0;
}