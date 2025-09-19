#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_IMAGE_SIZE 1024 * 1024 // 1MB

void convert_to_base64(const unsigned char *input, size_t input_len, char **output) {
    static const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int output_len = 4 * ((input_len + 2) / 3);
    *output = (char *)malloc(output_len + 1);
    if (*output == NULL) return;
    unsigned char a3[3];
    unsigned char a4[4];
    int i = 0, j = 0;
    while (input_len > 0) {
        a3[i++] = *(input++);
        input_len--;
        if (i == 3) {
            a4[0] = (a3[0] & 0xfc) >> 2;
            a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
            a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
            a4[3] = (a3[2] & 0x3f);
            for(i = 0; i < 4; i++) (*output)[j++] = b64chars[a4[i]];
            i = 0;
        }
    }
    if (i > 0) {
        for(j = i; j < 3; j++) a3[j] = '\0';
        a4[0] = (a3[0] & 0xfc) >> 2;
        a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
        a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
        a4[3] = (a3[2] & 0x3f);
        for(j = 0; j < i + 1; j++) (*output)[j] = b64chars[a4[j]];
        while(i++ < 3) (*output)[i] = '=';
    }
    (*output)[output_len] = '\0';
}

void upload_image(const char *filename, sqlite3 *db) {
    FILE *file = fopen(filename, "rb");
    if (!file) return;

    unsigned char image_buffer[MAX_IMAGE_SIZE];
    size_t file_size = fread(image_buffer, 1, MAX_IMAGE_SIZE, file);
    fclose(file);

    char *base64_image;
    convert_to_base64(image_buffer, file_size, &base64_image);

    const char *sql = "INSERT INTO images (name, base64) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        free(base64_image);
        return;
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_image, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {}

    sqlite3_finalize(stmt);
    free(base64_image);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("example.db", &db)) {
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY, name TEXT, base64 TEXT)";
    sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);

    upload_image("test.jpg", db);

    sqlite3_close(db);
    return 0;
}