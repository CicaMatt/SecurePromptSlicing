#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function prototypes
int callback(void *data, int argc, char **argv, char **azColName);
void upload_image(const char* image_name, const unsigned char* image_data, size_t data_size);

// Global database handle
sqlite3 *db;

int main() {
    // Initialize the database connection
    if (sqlite3_open("images.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table if it doesn't exist
    char *err_msg = NULL;
    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL UNIQUE, "
        "data BLOB);";

    if (sqlite3_exec(db, sql_create_table, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    // Example usage
    const char *image_name = "example.jpg";
    unsigned char image_data[] = { /* some binary data */ };
    upload_image(image_name, image_data, sizeof(image_data));

    sqlite3_close(db);
    return 0;
}

void upload_image(const char* image_name, const unsigned char* image_data, size_t data_size) {
    // Prepare SQL statement
    char sql_insert[256];
    snprintf(sql_insert, sizeof(sql_insert), "INSERT INTO images (name, data) VALUES ('%s', ?)", image_name);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Bind binary data
    sqlite3_bind_blob(stmt, 1, image_data, data_size, SQLITE_STATIC);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    // Clean up
    sqlite3_finalize(stmt);
}

int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}