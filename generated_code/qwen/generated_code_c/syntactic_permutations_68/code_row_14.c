#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "example.db"

void upload_image(const char* image_path) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char* sql_create_table = "CREATE TABLE IF NOT EXISTS images ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "name TEXT NOT NULL, "
                                   "data BLOB);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return;
    }

    FILE* image_file = fopen(image_path, "rb");
    if (!image_file) {
        fprintf(stderr, "Failed to open file for reading.\n");
        sqlite3_close(db);
        return;
    }

    fseek(image_file, 0, SEEK_END);
    long file_size = ftell(image_file);
    fseek(image_file, 0, SEEK_SET);

    unsigned char* image_data = (unsigned char*)malloc(file_size * sizeof(unsigned char));
    if (!image_data) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(image_file);
        sqlite3_close(db);
        return;
    }

    fread(image_data, file_size, 1, image_file);
    fclose(image_file);

    const char* sql_insert = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        free(image_data);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, image_path, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, image_data, file_size, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    free(image_data);
    sqlite3_close(db);
}

int main() {
    upload_image("path/to/your/image.jpg");
    return 0;
}