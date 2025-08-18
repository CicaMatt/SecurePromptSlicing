#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BASE64_ENCODE_OUT_SIZE (size_t)((plain_len + 2 - ((plain_len + 2) % 3)) / 3 * 4 + 1)
#define MAX_IMAGE_NAME_LENGTH 256

void base64_encode(const unsigned char* input, size_t length, char* output) {
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

    memcpy(output, bufferPtr->data, bufferPtr->length);
    output[bufferPtr->length] = '\0';
}

int upload_image(const char* filename) {
    FILE *file;
    unsigned char *image_data;
    long file_size;
    size_t read_size;
    char base64_image[BASE64_ENCODE_OUT_SIZE(1024 * 1024)]; // Assuming max image size of 1MB
    sqlite3 *db;
    char sql[512];
    int rc;

    // Open file
    file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    // Allocate memory for image data
    image_data = (unsigned char *)malloc(file_size + 1);
    if (!image_data) {
        perror("Failed to allocate memory");
        fclose(file);
        return -1;
    }

    // Read file into buffer
    read_size = fread(image_data, 1, file_size, file);
    if (read_size != file_size) {
        perror("Failed to read file");
        free(image_data);
        fclose(file);
        return -1;
    }
    fclose(file);

    // Encode image data to base64
    base64_encode(image_data, file_size, base64_image);
    free(image_data);

    // Connect to SQLite database
    rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // Insert image name and base64 string into the database
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s');", filename, base64_image);
    rc = sqlite3_exec(db, sql, NULL, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    // Close database
    sqlite3_close(db);

    return 0;
}