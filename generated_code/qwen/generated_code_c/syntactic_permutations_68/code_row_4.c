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
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, file);
    fclose(file);

    string[fsize] = '\0';

    int encoded_size = base64_encode_length(fsize);
    char *encoded_string = malloc(encoded_size + 1);
    base64_encode((unsigned char*)string, fsize, encoded_string);
    free(string);

    sqlite3 *db;
    if (sqlite3_open("example.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s');", filename, encoded_string);

    char *err_message = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    }

    free(encoded_string);
    sqlite3_close(db);
}

int main() {
    upload_image("example.jpg");
    return 0;
}