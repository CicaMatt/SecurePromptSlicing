#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "images.db"
#define MAX_IMAGE_NAME 256
#define MAX_BASE64_STRING 10000

int insert_image_into_db(const char *image_name, const char *base64_string) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char sql[2048];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO images (name, base64_data) VALUES ('%q', '%q');", 
             image_name, base64_string);

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

void upload_image(const char *image_name, const char *base64_string) {
    if (insert_image_into_db(image_name, base64_string)) {
        printf("Failed to insert image into database.\n");
    } else {
        printf("Image uploaded successfully.\n");
    }
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql = 
        "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "base64_data TEXT NOT NULL"
        ");";

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    // Example usage
    const char *image_name = "example.jpg";
    const char *base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."
    upload_image(image_name, base64_string);

    return 0;
}