#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "image_db.db"

int upload_image(const char *image_name, const char *base64_string) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "base64_data TEXT NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return rc;
    }

    char sql[1024];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO images (name, base64_data) VALUES ('%q', '%q');", 
             image_name, base64_string);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return rc;
    }

    sqlite3_close(db);
    return SQLITE_OK;
}

int main() {
    const char *image_name = "example.jpg";
    const char *base64_string = "iVBORw0KGgoAAAANSUhEUgAAADIA..."; // truncated for brevity

    int result = upload_image(image_name, base64_string);
    if (result == SQLITE_OK) {
        printf("Image uploaded successfully.\n");
    } else {
        printf("Failed to upload image.\n");
    }

    return 0;
}