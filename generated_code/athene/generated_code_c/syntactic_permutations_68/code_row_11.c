#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void upload_image(sqlite3 *db, const char *image_name, const char *base64_string) {
    if (db == NULL || image_name == NULL || base64_string == NULL) return;

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_string, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS images (" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "name TEXT NOT NULL," \
        "data TEXT NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *image_name = "example.jpg";
    const char *base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // Truncated for brevity

    upload_image(db, image_name, base64_string);

    sqlite3_close(db);
    return 0;
}