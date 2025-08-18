#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define DATABASE "images.db"
#define TABLE_NAME "images"

void upload_image(const char *image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *image_data = malloc(file_size);
    if (!image_data) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(image_data, 1, file_size, file);
    fclose(file);

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, image_data, file_size);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    char *base64_string = malloc(bufferPtr->length + 1);
    if (!base64_string) {
        perror("Memory allocation failed");
        free(image_data);
        BIO_free_all(bio);
        return;
    }

    memcpy(base64_string, bufferPtr->data, bufferPtr->length);
    base64_string[bufferPtr->length] = '\0';

    BIO_free_all(bio);
    free(image_data);

    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS images ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL,"
                "data BLOB NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    char *image_name = strrchr(image_path, '/');
    if (!image_name) image_name = (char *)image_path;
    else image_name++;

    sql = sqlite3_mprintf("INSERT INTO images (name, data) VALUES ('%q', '%q');", image_name, base64_string);
    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    sqlite3_free(sql);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("Image inserted successfully!\n");
    }

    free(base64_string);
    sqlite3_close(db);
}

int main() {
    upload_image("path/to/image.jpg");
    return 0;
}