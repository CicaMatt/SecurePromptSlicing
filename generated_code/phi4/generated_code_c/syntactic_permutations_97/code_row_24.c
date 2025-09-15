#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_LEN 256

void hash_password(const char *input, char *output) {
    for (int i = 0; input[i] != '\0' && i < MAX_LEN - 1; ++i) {
        output[i] = input[i] + 1; // Simple Caesar cipher for demonstration
    }
    output[strlen(input)] = '\0';
}

void register_user(sqlite3 *db, const char *username, const char *password, 
                   const char *first_name, const char *last_name, const char *email) {
    
    char hashed_password[MAX_LEN];
    hash_password(password, hashed_password);

    // Check if username already exists
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_int(stmt, 0) > 0) {
        printf("Username already exists.\n");
    } else {
        // Insert new user
        const char *insert_sql = "INSERT INTO users(username, password, first_name, last_name, email) VALUES(?, ?, ?, ?, ?);";
        if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL) != SQLITE_OK) {
            printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            return;
        }
        
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            printf("Failed to insert user: %s\n", sqlite3_errmsg(db));
        } else {
            printf("Registration succeeded.\n");
        }
    }
    
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table
    char *err_msg = NULL;
    const char *create_table_sql = 
        "CREATE TABLE users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL UNIQUE, "
        "password TEXT NOT NULL, "
        "first_name TEXT NOT NULL, "
        "last_name TEXT NOT NULL, "
        "email TEXT NOT NULL);";
    
    if (sqlite3_exec(db, create_table_sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    // Sample registration
    char username[MAX_LEN] = "john_doe";
    char password[MAX_LEN] = "securepassword123";
    char first_name[MAX_LEN] = "John";
    char last_name[MAX_LEN] = "Doe";
    char email[MAX_LEN] = "john.doe@example.com";

    register_user(db, username, password, first_name, last_name, email);

    // Attempt to register the same user again
    register_user(db, username, password, first_name, last_name, email);

    sqlite3_close(db);
    return 0;
}
