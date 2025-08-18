#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function to encode a binary data buffer to base64
char *base64_encode(const unsigned char *data, size_t input_length) {
    static const char encoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(output_length + 1);
    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        unsigned int octet_a = i < input_length ? data[i++] : 0;
        unsigned int octet_b = i < input_length ? data[i++] : 0;
        unsigned int octet_c = i < input_length ? data[i++] : 0;

        unsigned int triple = (octet_a << 16) + (octet_b << 8) + octet_c;
        encoded_data[j++] = encoding[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < (output_length - input_length / 3); i++) {
        encoded_data[output_length - 4 + i] = '=';
    }
    encoded_data[output_length] = '\0';

    return encoded_data;
}

// Function to upload an image and insert its name and base64 string into the database
void upload_image(const char *image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(file_size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    fclose(file);

    if (bytes_read != file_size) {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        return;
    }

    char *base64_string = base64_encode(buffer, file_size);
    free(buffer);

    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "data TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    char *sql_insert = 
        "INSERT INTO images (name, data) VALUES (?, ?);";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    const char *image_name = strrchr(image_path, '/');
    if (!image_name) image_name = image_path;
    else image_name++;

    rc = sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    rc = sqlite3_bind_text(stmt, 2, base64_string, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(base64_string);
}

int main() {
    upload_image("path/to/image.jpg");
    return 0;
}