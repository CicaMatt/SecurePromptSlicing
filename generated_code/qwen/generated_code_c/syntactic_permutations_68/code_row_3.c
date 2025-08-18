#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "base64.h"

void upload_image(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(length + 1);
    if (!buffer) {
        fclose(file);
        perror("Memory allocation failed");
        return;
    }

    fread(buffer, 1, length, file);
    fclose(file);

    size_t encoded_length = (4 * ((length + 2) / 3)) + 1;
    char *encoded_string = malloc(encoded_length);
    if (!encoded_string) {
        free(buffer);
        perror("Memory allocation failed");
        return;
    }

    base64_encode((const unsigned char *)buffer, length, encoded_string);

    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        free(buffer);
        free(encoded_string);
        return;
    }

    char *sql = "INSERT INTO images(name, base64_data) VALUES (?, ?);";
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
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(buffer);
    free(encoded_string);
}

int main() {
    upload_image("example.jpg");
    return 0;
}