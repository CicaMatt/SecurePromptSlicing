#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_IMAGE_SIZE 1024 * 1024 // 1MB
#define BASE64_ENCODED_LENGTH(length) ((length + 2) / 3 * 4)

void encode_base64(const unsigned char *input, size_t input_length, char *output) {
    static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i = 0;
    int j = 0;
    unsigned char triple[3];
    while (input_length--) {
        triple[i++] = *(input++);
        if (i == 3) {
            output[j++] = base64_chars[(triple[0] & 0xFC) >> 2];
            output[j++] = base64_chars[((triple[0] & 0x03) << 4) | ((triple[1] & 0xF0) >> 4)];
            output[j++] = base64_chars[((triple[1] & 0x0F) << 2) | ((triple[2] & 0xC0) >> 6)];
            output[j++] = base64_chars[triple[2] & 0x3F];
            i = 0;
        }
    }
    if (i) {
        for (int k = i; k < 3; k++) {
            triple[k] = '\0';
        }
        output[j++] = base64_chars[(triple[0] & 0xFC) >> 2];
        output[j++] = base64_chars[((triple[0] & 0x03) << 4) | ((triple[1] & 0xF0) >> 4)];
        output[j++] = (i == 1) ? '=' : base64_chars[((triple[1] & 0x0F) << 2) | ((triple[2] & 0xC0) >> 6)];
        output[j++] = '=';
    }
    output[j] = '\0';
}

int upload_image(const char *filename, sqlite3 *db) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    unsigned char image_data[MAX_IMAGE_SIZE];
    size_t bytes_read = fread(image_data, 1, MAX_IMAGE_SIZE, file);
    fclose(file);

    size_t base64_length = BASE64_ENCODED_LENGTH(bytes_read);
    char *base64_string = (char *)malloc(base64_length + 1);
    if (!base64_string) {
        perror("Failed to allocate memory for base64 string");
        return 1;
    }

    encode_base64(image_data, bytes_read, base64_string);

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        free(base64_string);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_string, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        free(base64_string);
        return 1;
    }

    sqlite3_finalize(stmt);
    free(base64_string);
    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *filename = "example.jpg";
    upload_image(filename, db);

    sqlite3_close(db);
    return 0;
}