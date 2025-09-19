#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void upload_image(const char *imageName, const char *base64Data) {
    sqlite3 *db;
    char *errMsg = NULL;
    int rc;

    // Open database
    rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Create table if it doesn't exist
    const char *sqlCreateTable = 
        "CREATE TABLE IF NOT EXISTS images("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL UNIQUE,"
        "data BLOB);";

    rc = sqlite3_exec(db, sqlCreateTable, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // Insert image
    char *sqlInsertImage = 
        "INSERT INTO images(name, data) VALUES(?, ?);";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sqlInsertImage, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Bind values
    sqlite3_bind_text(stmt, 1, imageName, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, base64Data, strlen(base64Data), SQLITE_STATIC);

    // Execute statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert image: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Image uploaded successfully.\n");
    }

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    const char *imageName = "example.png";
    const char *base64Data = "iVBORw0KGgoAAAANSUhEUgAAAAUA...";
    
    upload_image(imageName, base64Data);

    return 0;
}