#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_IMAGE_SIZE 1024 * 1024 // 1MB
#define BASE64_ENCODED_SIZE(x) ((x + 2 - ((x + 2) % 3)) / 3 * 4)

void encode_base64(const unsigned char *src, size_t len, char *out) {
    static const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (size_t i = 0; i < len; ) {
        out[i / 3 * 4 + 0] = table[src[i++] >> 2];
        out[i / 3 * 4 + 1] = table[((src[i - 1] & 0x03) << 4) | (i < len ? src[i] >> 4 : 0)];
        out[i / 3 * 4 + 2] = i + 1 < len ? table[((src[i++] & 0x0F) << 2) | (i < len ? src[i] >> 6 : 0)] : '=';
        out[i / 3 * 4 + 3] = i < len ? table[src[i++] & 0x3F] : '=';
    }
}

void upload_image(const char *image_path) {
    FILE *fp = fopen(image_path, "rb");
    if (!fp) {
        perror("Failed to open image file");
        return;
    }

    unsigned char buffer[MAX_IMAGE_SIZE];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);

    if (bytes_read == 0) {
        fprintf(stderr, "No data read from the image file\n");
        return;
    }

    char base64_buffer[BASE64_ENCODED_SIZE(bytes_read) + 1];
    encode_base64(buffer, bytes_read, base64_buffer);
    base64_buffer[BASE64_ENCODED_SIZE(bytes_read)] = '\0';

    sqlite3 *db;
    if (sqlite3_open("example.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char *err_msg = 0;
    const char *sql = "CREATE TABLE IF NOT EXISTS images (name TEXT, data TEXT);";
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    char *image_name = strrchr(image_path, '/');
    if (image_name) image_name++;
    else image_name = (char *)image_path;

    sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_buffer, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    upload_image("path/to/image.jpg");
    return 0;
}