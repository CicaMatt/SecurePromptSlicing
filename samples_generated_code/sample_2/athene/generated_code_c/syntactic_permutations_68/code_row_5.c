#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void upload_image(const char *image_name, const char *base64_string) {
    sqlite3 *db;
    int rc;
    char *err_msg = 0;

    // Open the database
    rc = sqlite3_open("images.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *sql = "INSERT INTO images (name, data) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, base64_string, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Image uploaded successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}