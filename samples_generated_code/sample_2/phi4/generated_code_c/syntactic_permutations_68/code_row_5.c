#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function declarations
int callback(void *NotUsed, int argc, char **argv, char **azColName);
void upload_image(const char* image_name, const char* base64_string);

int main() {
    // Example usage of the upload_image function
    const char* image_name = "example.jpg";
    const char* base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA...";
    
    upload_image(imagename, base64_string);
    
    return 0;
}

void upload_image(const char *image_name, const char *base64_string) {
    sqlite3 *db;
    char *err_msg = 0;

    // Open database connection
    int rc = sqlite3_open("images.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Create table if it does not exist
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS images "
        "(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, data TEXT NOT NULL);";
    
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    // Prepare SQL statement
    char *sql_insert = sqlite3_mprintf("INSERT INTO images(name, data) VALUES(?, ?);");

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_free(sql_insert);
        sqlite3_close(db);
        return;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, image_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, base64_string, -1, SQLITE_STATIC);

    // Execute SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_free(sql_insert);
    sqlite3_close(db);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    (void) NotUsed;
    
    for(int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    return 0;
}