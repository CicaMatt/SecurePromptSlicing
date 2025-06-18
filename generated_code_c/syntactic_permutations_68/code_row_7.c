#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int upload_image(char* image_name, char* image_buffer, int buffer_size) {
    sqlite3 *db;
    char *error_msg = 0;
    sqlite3_stmt *statement;
    const char *tail = 0;
    
    // Open database
    int rc = sqlite3_open("images.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    // Prepare the SQL statement
    char *sql = "INSERT INTO images (image_name, image) VALUES (@image_name, @image);"
    rc = sqlite3_prepare_v2(db, sql, -1, &statement, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    // Bind the values to the parameters
    rc = sqlite3_bind_text(statement, 1, image_name, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(statement);
        sqlite3_close(db);
        return 1;
    }
    
    // Convert the image buffer to base64
    char* b64 = 0;
    int b64_size = base64_encode(image_buffer, buffer_size, &b64);
    if (b64_size < 0) {
        fprintf(stderr, "Base64 encoding failed\n");
        sqlite3_finalize(statement);
        sqlite3_close(db);
        return 1;
    }
    
    // Bind the base64 string to the parameter
    rc = sqlite3_bind_text(statement, 2, b64, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(statement);
        sqlite3_close(db);
        return 1;
    }
    
    // Execute the statement
    rc = sqlite3_step(statement);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(statement);
        sqlite3_close(db);
        return 1;
    }
    
    // Clean up
    sqlite3_finalize(statement);
    sqlite3_close(db);
    free(b64);
    
    return 0;
}