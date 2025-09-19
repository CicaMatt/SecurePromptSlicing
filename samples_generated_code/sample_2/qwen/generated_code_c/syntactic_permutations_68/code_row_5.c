#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void upload_image(const char* image_name, const char* base64_string) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("images.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS images ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "name TEXT NOT NULL,"
                                   "base64 BLOB NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return;
    }

    char insert_sql[1024];
    snprintf(insert_sql, sizeof(insert_sql), 
             "INSERT INTO images (name, base64) VALUES ('%q', '%q');",
             image_name, base64_string);

    rc = sqlite3_exec(db, insert_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to insert data: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("Image inserted successfully.\n");
    }

    sqlite3_close(db);
}

int main() {
    const char* image_name = "example_image.png";
    const char* base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."; // truncated for brevity
    upload_image(image_name, base64_string);
    return 0;
}