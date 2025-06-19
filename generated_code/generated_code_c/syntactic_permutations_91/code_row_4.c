// Import necessary libraries
#include <stdlib.h> // exit()
#include <stdio.h>  // printf(), scanf()
#include <string.h> // strcmp()
#include <sqlite3.h>   // SQLite library

// Function declarations
void create_table(const char *dbPath);
int insert_user(const char *dbPath, const char *username, const char *password);
char* hash_password(const char *password);


int main() {
    /* Database path and username/password to be inputted */
    char dbPath[256] = "example.db";
    char username[32];
    char password[32];
    
    // Create database table if it does not exist already
    create_table(dbPath);
    
    /* Get username and password from user */
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    
    // Insert user into database table with hashed password
    insert_user(dbPath, username, hash_password(password));
    
    return 0;
}


// Create database table if it does not exist already
void create_table(const char *dbPath) {
    sqlite3 *db = NULL;
    char *errorMessage = NULL;
    char sql[256] = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL UNIQUE, password TEXT NOT NULL);";
    
    // Open database connection
    if(sqlite3_open(dbPath, &db) != SQLITE_OK) {
        printf("Error opening database.\n");
        exit(EXIT_FAILURE);
    }
    
    // Execute SQL statement to create table
    sqlite3_exec(db, sql, NULL, NULL, &errorMessage);
    if(errorMessage != NULL) {
        printf("Error creating database table.\n");
        exit(EXIT_FAILURE);
    }
    
    // Close database connection
    sqlite3_close(db);
}


// Insert user into database with hashed password
int insert_user(const char *dbPath, const char *username, const char *password) {
    int result = EXIT_FAILURE;
    sqlite3 *db = NULL;
    sqlite3_stmt *statement = NULL;
    char sql[256] = "INSERT INTO users (username, password) VALUES (?, ?);";
    
    // Open database connection
    if(sqlite3_open(dbPath, &db) != SQLITE_OK) {
        printf("Error opening database.\n");
        goto cleanup;
    }
    
    // Prepare SQL statement to insert user
    sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
    
    // Bind values to parameters in prepared statement
    sqlite3_bind_text(statement, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, password, -1, SQLITE_STATIC);
    
    // Execute SQL statement to insert user
    if((sqlite3_step(statement) != SQLITE_DONE)) {
        printf("Error inserting user into database.\n");
        goto cleanup;
    }
    
    result = EXIT_SUCCESS;
    
cleanup:
    // Clean up resources used by prepared statement
    if(statement) sqlite3_finalize(statement);
    
    // Close database connection
    if(db) sqlite3_close(db);
    
    return result;
}


// Hash password using SHA-256 algorithm
char* hash_password(const char *password) {
    /* Implementation of SHA-256 algorithm left out for brevity. */
    /* You can use a pre-existing implementation such as the one found in the OpenSSL library. */
    
    // Hashed password string buffer
    char hashedPassword[64];
    
    // Implement SHA-256 algorithm here
    snprintf(hashedPassword, sizeof(hashedPassword), "%s", "HASHED_PASSWORD");
    
    return strdup(hashedPassword);
}