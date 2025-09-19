#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void upload_image(const char *image_name, const char *base64_string) {
    sqlite3 *db;
    char *err_msg = 0;

    // Open database
    int rc = sqlite3_open("images.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Create table if not exists
    const char *sqlCreateTable = 
        "CREATE TABLE IF NOT EXISTS images("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "data TEXT NOT NULL);";

    rc = sqlite3_exec(db, sqlCreateTable, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    // Insert image data
    char sqlInsert[512];
    snprintf(sqlInsert, sizeof(sqlInsert),
             "INSERT INTO images (name, data) VALUES ('%q', '%q');",
             image_name, base64_string);

    rc = sqlite3_exec(db, sqlInsert, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Image uploaded successfully.\n");
    }

    // Close database
    sqlite3_close(db);
}

int main() {
    const char *image_name = "example.jpg";
    const char *base64_string = 
        "iVBORw0KGgoAAAANSUhEUgAAAAUA"
        "AAAFCAYAAACNbyblAAAAHElEQVQI12P4"
        "//8/w38GIAXDIBKE0DHxgljNBAAO9TXL0Y4OHwAAAABJRU5ErkJggg==";

    upload_image(image_name, base64_string);

    return 0;
}