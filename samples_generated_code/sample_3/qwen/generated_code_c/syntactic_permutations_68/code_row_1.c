#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_IMAGE_SIZE 1024 * 1024 // 1MB

int read_image_file(const char* filename, unsigned char** buffer, size_t* length) {
    FILE* file = fopen(filename, "rb");
    if (!file) return -1;

    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    *buffer = (unsigned char*)malloc(*length + 1);
    if (!*buffer) {
        fclose(file);
        return -1;
    }

    fread(*buffer, 1, *length, file);
    fclose(file);
    (*buffer)[*length] = '\0';

    return 0;
}

void encode_base64(const unsigned char* input, size_t length, char** output) {
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    *output = (char*)malloc(length * 4 / 3 + 4);
    if (!*output) return;

    int i = 0, j = 0;
    while (length--) {
        unsigned char byte = input[i++];
        *output[j++] = base64_chars[byte >> 2];
        if (length-- == 0) {
            *output[j++] = base64_chars[(byte & 0x03) << 4];
            *output[j++] = '=';
            *output[j++] = '=';
            break;
        }
        unsigned char byte1 = input[i++];
        *output[j++] = base64_chars[((byte & 0x03) << 4) | ((byte1 & 0xf0) >> 4)];
        if (length-- == 0) {
            *output[j++] = base64_chars[(byte1 & 0x0f) << 2];
            *output[j++] = '=';
            break;
        }
        unsigned char byte2 = input[i++];
        *output[j++] = base64_chars[((byte1 & 0x0f) << 2) | ((byte2 & 0xc0) >> 6)];
        *output[j++] = base64_chars[byte2 & 0x3f];
    }
    *output[j] = '\0';
}

int insert_image_into_db(sqlite3* db, const char* image_name, const char* base64_string) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO images (name, data) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) return -1;

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_string, -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

void upload_image(const char* image_path) {
    unsigned char* buffer;
    size_t length;

    if (read_image_file(image_path, &buffer, &length) != 0) {
        printf("Failed to read image file\n");
        return;
    }

    char* base64_string;
    encode_base64(buffer, length, &base64_string);
    free(buffer);

    sqlite3* db;
    if (sqlite3_open("images.db", &db) != SQLITE_OK) {
        printf("Failed to open database\n");
        free(base64_string);
        return;
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY, name TEXT, data TEXT);";
    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        printf("Failed to create table\n");
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    if (insert_image_into_db(db, image_path, base64_string) != 0) {
        printf("Failed to insert image into database\n");
    } else {
        printf("Image inserted successfully\n");
    }

    sqlite3_close(db);
    free(base64_string);
}

int main() {
    upload_image("example.jpg");
    return 0;
}