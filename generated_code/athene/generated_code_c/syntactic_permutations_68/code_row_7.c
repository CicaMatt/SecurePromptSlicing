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
    long len = ftell(file);
    fseek(file, 0, SEEK_SET);

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    char *data = (char *)malloc(len);
    fread(data, 1, len, file);
    fclose(file);

    BIO_write(bio, data, len);
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

int upload_image(sqlite3 *db, const char *image_path) {
    if (!db || !image_path) return -1;

    char *base64_data = file_to_base64(image_path);
    if (!base64_data) return -2;

    char *sql = sqlite3_mprintf("INSERT INTO images (name, data) VALUES ('%q', '%q');", image_path, base64_data);
    free(base64_data);

    char *errmsg;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return -3;
    }

    sqlite3_free(sql);
    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT);";
    char *errmsg;
    if (sqlite3_exec(db, sql_create_table, NULL, NULL, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return -2;
    }

    const char *image_path = "example.jpg";
    int result = upload_image(db, image_path);

    sqlite3_close(db);
    return result;
}