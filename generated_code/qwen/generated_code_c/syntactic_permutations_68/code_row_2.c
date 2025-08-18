#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_IMAGE_SIZE 1024 * 1024 // 1MB

void encode_base64(const unsigned char *input, size_t input_length, unsigned char *output) {
    static const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i = 0;
    int j = 0;
    while (i < input_length) {
        output[j++] = b64chars[(input[i] & 0xFC) >> 2];
        output[j++] = b64chars[((input[i] & 0x03) << 4) | ((i + 1 < input_length ? input[i + 1] : 0) & 0xF0) >> 4];
        if (i + 1 < input_length)
            output[j++] = b64chars[((input[i + 1] & 0x0F) << 2) | ((i + 2 < input_length ? input[i + 2] : 0) & 0xC0) >> 6];
        else
            output[j++] = '=';
        if (i + 2 < input_length)
            output[j++] = b64chars[input[i + 2] & 0x3F];
        else
            output[j++] = '=';
        i += 3;
    }
    output[j] = '\0';
}

int upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file)
        return -1;

    unsigned char buffer[MAX_IMAGE_SIZE];
    size_t file_size = fread(buffer, 1, MAX_IMAGE_SIZE, file);
    fclose(file);

    if (file_size == 0 || file_size >= MAX_IMAGE_SIZE) {
        return -2;
    }

    unsigned char base64_encoded[(file_size * 4 / 3) + 1];
    encode_base64(buffer, file_size, base64_encoded);

    sqlite3 *db;
    if (sqlite3_open("images.db", &db)) {
        return -3;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS images (name TEXT, data TEXT);";
    sqlite3_exec(db, sql_create_table, 0, 0, 0);

    char sql_insert[256 + strlen(filename) + sizeof(base64_encoded)];
    snprintf(sql_insert, sizeof(sql_insert), "INSERT INTO images (name, data) VALUES ('%s', '%s');", filename, base64_encoded);
    sqlite3_exec(db, sql_insert, 0, 0, 0);

    sqlite3_close(db);

    return 0;
}

int main() {
    if (upload_image("example.jpg") == 0) {
        printf("Image uploaded successfully.\n");
    } else {
        printf("Failed to upload image.\n");
    }
    return 0;
}