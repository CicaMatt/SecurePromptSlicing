#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function to convert a file to Base64
char *file_to_base64(const char *filename, size_t *out_size) {
    FILE *f = fopen(filename, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    unsigned char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, f);
    fclose(f);

    static const char base64_chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    size_t len = (((fsize + 2) / 3) * 4);
    char *encoded_data = malloc(len + 1);
    if (!encoded_data) {
        free(buffer);
        return NULL;
    }

    unsigned int i, j;
    for (i = 0, j = 0; i < fsize;) {
        uint32_t octet_a = i < fsize ? buffer[i++] : 0;
        uint32_t octet_b = i < fsize ? buffer[i++] : 0;
        uint32_t octet_c = i < fsize ? buffer[i++] : 0;

        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        encoded_data[j++] = base64_chars[(triple >> 18) & 63];
        encoded_data[j++] = base64_chars[(triple >> 12) & 63];
        encoded_data[j++] = i > fsize + 1 ? '=' : base64_chars[(triple >> 6) & 63];
        encoded_data[j++] = i > fsize + 2 ? '=' : base64_chars[triple & 63];
    }

    encoded_data[len] = '\0';
    free(buffer);
    *out_size = len;
    return encoded_data;
}

// Callback function for SQLite
int callback(void *data, int argc, char **argv, char **azColName) {
    (void)data; (void)argc; (void)argv; (void)azColName;
    return 0;
}

void upload_image(const char *image_path, const char *db_path) {
    size_t encoded_size = 0;
    char *encoded_image = file_to_base64(image_path, &encoded_size);
    if (!encoded_image) {
        fprintf(stderr, "Failed to encode image\n");
        return;
    }

    sqlite3 *db;
    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO images (image_name, base64_data) VALUES ('%s', '%.*s')",
             strrchr(image_path, '/') + 1, (int)encoded_size, encoded_image);

    if (sqlite3_open(db_path, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        free(encoded_image);
        return;
    }

    char *err_msg = NULL;
    if (sqlite3_exec(db, sql, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Image uploaded successfully.\n");
    }

    sqlite3_close(db);
    free(encoded_image);
}

int main() {
    const char *image_path = "path/to/image.jpg";
    const char *db_path = "images.db";

    // Create a table if it doesn't exist
    sqlite3 *db;
    if (sqlite3_open(db_path, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *err_msg = NULL;
    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "image_name TEXT NOT NULL,"
        "base64_data TEXT NOT NULL);";

    if (sqlite3_exec(db, sql_create_table, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    upload_image(image_path, db_path);

    sqlite3_close(db);
    return 0;
}