#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE_NAME "image_database.db"
#define TABLE_NAME "images"

void upload_image(const char *image_name, const char *base64_string) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open(DATABASE_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "base64_data TEXT NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO images (name, base64_data) VALUES ('%q', '%q');",
             image_name, base64_string);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("Image inserted successfully.\n");
    }

    sqlite3_close(db);
}

int main() {
    const char *image_name = "example.jpg";
    const char *base64_string = "/9j/4AAQSkZJRgABAQAAAQABAAD/2wBDAAgGBwgHBgkIBwgKCgkLDRYPDQwMDRsUFRAWIB0WMBhMFYAPExJaYQrCeY6SltMlclKztfQ0AkKGIjGdIyJjKSkrMC8vDC0oMCUoKSj/2wBDAQkJCQwLDBgNDRgyIR4cHCAgIREgIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIiIi/8AAEQgAQAFAwEiAAIRAQMRAf/EAB0AAAEEAAUBAQAAAAAAAAAAAAACAwQFBgcICQoL/8QAtRAAAgEDAwIEAgUEBQYHBQQDAAECESEDEhMhMRJBUWEGYXGBkRciMxNyU1NjcpKhsrN0BHQlYnNzZ3c4Ny8wY3R2dndvL08vdGZ0eXx5fj8PPC9P/8QAFAEBAAAAAAAAAAAAAAAAAAAAAP/EABQRAQAAAAAAAAAAAAAAAAAAAAD/2gAMAwEAAhEDEQA/AJ+D/AP/Z";

    upload_image(image_name, base64_string);

    return 0;
}