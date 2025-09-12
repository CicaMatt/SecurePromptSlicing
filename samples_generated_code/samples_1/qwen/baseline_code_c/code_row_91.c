#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define BUFFER_SIZE 1024

void upload_image(const char* filename, sqlite3* db) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileLen = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fileLen + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, fileLen, 1, file);
    fclose(file);
    buffer[fileLen] = '\0';

    // Base64 encoding
    int encodedSize = (fileLen + 2) / 3 * 4;
    char *base64 = (char *)malloc(encodedSize + 1);
    if (!base64) {
        perror("Memory allocation failed");
        free(buffer);
        return;
    }

    const char base64_chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    for (int i = 0, j = 0; i < fileLen;) {
        unsigned int octetA = i < fileLen ? (unsigned char)buffer[i++] : 0;
        unsigned int octetB = i < fileLen ? (unsigned char)buffer[i++] : 0;
        unsigned int octetC = i < fileLen ? (unsigned char)buffer[i++] : 0;

        unsigned int triple = (octetA << 16) + (octetB << 8) + octetC;

        base64[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
        base64[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
        base64[j++] = (i < fileLen + 2) ? base64_chars[(triple >> 1 * 6) & 0x3F] : '=';
        base64[j++] = (i < fileLen + 1) ? base64_chars[(triple >> 0 * 6) & 0x3F] : '=';
    }
    base64[encodedSize] = '\0';

    // Insert into database
    char *sql;
    sqlite3_stmt *stmt;

    sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        free(buffer);
        free(base64);
        return;
    }

    sqlite3_bind_text(stmt, 1, filename, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    free(buffer);
    free(base64);
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;

    if (sqlite3_open("images.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "data TEXT NOT NULL);";

    if (sqlite3_exec(db, sql_create_table, 0, 0, &zErrMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    upload_image("example.jpg", db);

    sqlite3_close(db);
    return 0;
}