#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_IMAGE_NAME_LENGTH 256
#define MAX_BASE64_STRING_LENGTH 1048576 // Assuming a maximum base64 string length of 1MB

int upload_image(const char* image_name, const char* base64_string) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("images.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS images ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "name TEXT NOT NULL,"
                                   "base64_string TEXT NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char insert_sql[1048576]; // Buffer to hold the SQL insert statement
    snprintf(insert_sql, sizeof(insert_sql), 
             "INSERT INTO images (name, base64_string) VALUES ('%s', '%s');", 
             image_name, base64_string);

    rc = sqlite3_exec(db, insert_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int main() {
    const char* image_name = "example_image.png";
    const char* base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..." // Example truncated base64 string

    if (upload_image(image_name, base64_string) == 0) {
        printf("Image uploaded successfully.\n");
    } else {
        printf("Failed to upload image.\n");
    }

    return 0;
}