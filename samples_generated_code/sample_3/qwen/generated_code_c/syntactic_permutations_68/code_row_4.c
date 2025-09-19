#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_IMAGE_SIZE 1024 * 1024 // Maximum size of the image in bytes
#define BASE64_BUFFER_SIZE ((MAX_IMAGE_SIZE / 3) * 4) + 1

// Function to convert binary data to base64
void encode_base64(const unsigned char* input, int length, unsigned char* output) {
    static const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i, j;
    unsigned long o = 0;

    for (i = 0; i < length - 2; i += 3) {
        output[o++] = encoding_table[input[i] >> 2];
        output[o++] = encoding_table[((input[i] & 0x03) << 4) | ((input[i + 1] & 0xfc) >> 4)];
        output[o++] = encoding_table[((input[i + 1] & 0x0f) << 2) | ((input[i + 2] & 0xc0) >> 6)];
        output[o++] = encoding_table[input[i + 2] & 0x3f];
    }

    if (i < length) {
        output[o++] = encoding_table[input[i] >> 2];
        if (i == length - 1) {
            output[o++] = encoding_table[(input[i] & 0x03) << 4];
            output[o++] = '=';
            output[o++] = '=';
        } else {
            output[o++] = encoding_table[((input[i] & 0x03) << 4) | ((input[i + 1] & 0xfc) >> 4)];
            output[o++] = encoding_table[(input[i + 1] & 0x0f) << 2];
            output[o++] = '=';
        }
    }

    output[o] = '\0';
}

void upload_image(const char* filename, const char* db_path) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    unsigned char image_buffer[MAX_IMAGE_SIZE];
    size_t bytes_read = fread(image_buffer, 1, MAX_IMAGE_SIZE, file);
    fclose(file);

    if (bytes_read == 0) {
        fprintf(stderr, "File is empty or read failed\n");
        return;
    }

    unsigned char base64_image[BASE64_BUFFER_SIZE];
    encode_base64(image_buffer, bytes_read, base64_image);

    sqlite3* db;
    int rc = sqlite3_open(db_path, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char* err_msg = NULL;
    const char* sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, (const char*)base64_image, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    const char* filename = "example.jpg";
    const char* db_path = "./images.db";

    upload_image(filename, db_path);

    return 0;
}