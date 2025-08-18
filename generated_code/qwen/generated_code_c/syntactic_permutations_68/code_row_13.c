#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_IMAGE_SIZE 1024 * 1024 * 5 // 5MB max size for images

void upload_image(const char* image_path) {
    FILE *image_file = fopen(image_path, "rb");
    if (!image_file) {
        perror("Failed to open the image file");
        return;
    }

    fseek(image_file, 0, SEEK_END);
    long image_size = ftell(image_file);
    rewind(image_file);

    if (image_size > MAX_IMAGE_SIZE) {
        fprintf(stderr, "Image size exceeds maximum allowed size.\n");
        fclose(image_file);
        return;
    }

    unsigned char* image_data = malloc(image_size);
    if (!image_data) {
        perror("Failed to allocate memory for the image data");
        fclose(image_file);
        return;
    }

    fread(image_data, 1, image_size, image_file);
    fclose(image_file);

    int base64_length = (image_size * 4 / 3) + 1;
    char* base64_string = malloc(base64_length);
    if (!base64_string) {
        perror("Failed to allocate memory for the base64 string");
        free(image_data);
        return;
    }

    const int B64_CHARS_PER_24_BITS = 4;
    const int BITS_PER_CHAR = 8;
    const int BITS_PER_GROUP = 24;

    unsigned char b64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for (int i = 0, j = 0; i < image_size; i += 3) {
        unsigned int group = ((unsigned int)(image_data[i]) << 16) |
                             ((i + 1 < image_size ? (unsigned int)(image_data[i + 1]) : 0) << 8) |
                             (i + 2 < image_size ? (unsigned int)(image_data[i + 2]) : 0);

        for (int k = B64_CHARS_PER_24_BITS - 1; k >= 0; --k, ++j)
            base64_string[j] = b64_chars[(group >> (k * (BITS_PER_CHAR))) & ((1 << BITS_PER_GROUP) - 1)];

        if (i + 1 < image_size && i + 2 == image_size)
            base64_string[j - 1] = '=';
        else if (i + 1 == image_size)
            base64_string[j - 2] = base64_string[j - 1] = '=';
    }
    base64_string[base64_length - 1] = '\0';

    free(image_data);

    sqlite3 *db;
    if (sqlite3_open("images.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        free(base64_string);
        return;
    }

    char* sql = "CREATE TABLE IF NOT EXISTS images("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL,"
                "data TEXT NOT NULL);";
    if (sqlite3_exec(db, sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    char* tail;
    const char* filename = strrchr(image_path, '/');
    if (!filename) {
        filename = image_path;
    } else {
        filename++;
    }
    int name_len = strlen(filename);
    int sql_len = snprintf(NULL, 0,
                           "INSERT INTO images (name, data) VALUES (?, ?);") + name_len + base64_length;
    char* insert_sql = malloc(sql_len);
    if (!insert_sql) {
        perror("Failed to allocate memory for the SQL statement");
        sqlite3_close(db);
        free(base64_string);
        return;
    }
    snprintf(insert_sql, sql_len,
             "INSERT INTO images (name, data) VALUES ('%s', '%s');", filename, base64_string);

    if (sqlite3_exec(db, insert_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        free(insert_sql);
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    free(insert_sql);
    sqlite3_close(db);
    free(base64_string);
}

int main() {
    upload_image("path/to/image.jpg");
    return 0;
}