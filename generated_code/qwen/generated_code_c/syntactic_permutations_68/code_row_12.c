#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "images.db"

void insertImageIntoDatabase(const char* imageName, const char* base64String) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS images("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "name TEXT NOT NULL, "
                                 "data TEXT NOT NULL);";
    rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    }

    char* sqlInsert = sqlite3_mprintf("INSERT INTO images (name, data) VALUES ('%q', '%q');",
                                      imageName, base64String);
    rc = sqlite3_exec(db, sqlInsert, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Image inserted successfully.\n");
    }

    sqlite3_free(sqlInsert);
    sqlite3_close(db);
}

void upload_image(const char* imageName, const char* base64String) {
    insertImageIntoDatabase(imageName, base64String);
}

int main() {
    // Example usage
    const char* imageName = "example.jpg";
    const char* base64String = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."
                                // Base64 string would be much longer in reality

    upload_image(imageName, base64String);

    return 0;
}