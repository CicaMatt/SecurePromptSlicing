#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int upload_image(sqlite3 *db, const char *image_name, const char *base64_string) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO images (name, base64_data) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_string, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int main() {
    sqlite3 *db;
    const char *db_file = "image_db.db";
    if (sqlite3_open(db_file, &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table if it doesn't exist
    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS images ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT NOT NULL, "
            "base64_data TEXT NOT NULL);";
    if (sqlite3_exec(db, create_table_sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Example usage of upload_image
    const char *image_name = "example.png";
    const char *base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // truncated for brevity

    if (upload_image(db, image_name, base64_string) != 0) {
        fprintf(stderr, "Failed to upload image\n");
        sqlite3_close(db);
        return 1;
    }

    printf("Image uploaded successfully\n");

    sqlite3_close(db);
    return 0;
}