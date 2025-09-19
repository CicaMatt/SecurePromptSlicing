#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void upload_image(sqlite3 *db, const char *image_name, const char *base64_string) {
    if (db == NULL || image_name == NULL || base64_string == NULL) return;

    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s');", image_name, base64_string);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Error inserting data: %s\n", sqlite3_errmsg(db));
        }
    } else {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("images.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS images (" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "name TEXT NOT NULL," \
        "data TEXT NOT NULL);";

    if (sqlite3_exec(db, sql_create_table, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *image_name = "example.png";
    const char *base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // truncated base64 string

    upload_image(db, image_name, base64_string);

    sqlite3_close(db);
    return 0;
}