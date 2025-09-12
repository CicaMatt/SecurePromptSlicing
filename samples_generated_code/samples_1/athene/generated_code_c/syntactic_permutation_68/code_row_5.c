#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void upload_image(sqlite3 *db, const char *image_name, const char *base64_string) {
    if (db == NULL || image_name == NULL || base64_string == NULL) return;

    char sql[1024];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s');", image_name, base64_string);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, data TEXT);";
    char *err_msg = 0;
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    const char *image_name = "example.png";
    const char *base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA...";
    upload_image(db, image_name, base64_string);

    sqlite3_close(db);
    return 0;
}