#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h> // For Windows specific functionality, if needed
#else
#include <unistd.h>
#endif

#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <jpeglib.h>

// Function to convert image to Base64
char* image_to_base64(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    unsigned char *data = (unsigned char*)malloc(length);
    fread(data, 1, length, file);
    fclose(file);

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, data, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    char *base64 = (char*)malloc(bufferPtr->length + 1);
    memcpy(base64, bufferPtr->data, bufferPtr->length);
    base64[bufferPtr->length] = '\0';

    BIO_free_all(bio);
    free(data);

    return base64;
}

// Function to insert image data into SQLite database
int upload_image(const char *image_path) {
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("images.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "base64_data TEXT);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return -1;
    }

    char *base64_data = image_to_base64(image_path);
    if (!base64_data) {
        fprintf(stderr, "Failed to convert image to base64.\n");
        sqlite3_close(db);
        return -1;
    }

    char sql_insert[512];
    snprintf(sql_insert, sizeof(sql_insert),
             "INSERT INTO images (name, base64_data) VALUES ('%s', '%s');",
             strrchr(image_path, '/') + 1, base64_data);

    rc = sqlite3_exec(db, sql_insert, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Image uploaded successfully.\n");
    }

    free(base64_data);

    sqlite3_close(db);
    return rc == SQLITE_OK ? 0 : -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (upload_image(argv[1]) != 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}