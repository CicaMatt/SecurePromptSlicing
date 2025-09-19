#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "base64.c"

void upload_image(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(length + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, length, file);
    fclose(file);
    buffer[length] = '\0';

    int encoded_length = Base64encode_len(length);
    char *encoded_string = (char *)malloc(encoded_length + 1);
    if (!encoded_string) {
        perror("Memory allocation failed");
        free(buffer);
        return;
    }

    Base64encode(encoded_string, (const char *)buffer, length);

    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("example.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(buffer);
        free(encoded_string);
        return;
    }

    char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(buffer);
        free(encoded_string);
        return;
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, encoded_string, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        free(buffer);
        free(encoded_string);
        return;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    free(buffer);
    free(encoded_string);
}

int main() {
    upload_image("example.png");
    return 0;
}