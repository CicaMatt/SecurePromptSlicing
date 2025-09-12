#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

// Function to hash a password using SHA-256
void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)password, strlen(password), hashed);
}

// Function to convert binary data to a hexadecimal string
void bin_to_hex(unsigned char *bin, size_t len, char *hex) {
    for (size_t i = 0; i < len; i++) {
        sprintf(hex + (i * 2), "%02x", bin[i]);
    }
}

// Callback function used by SQLite to handle query results
int callback(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

// Function to check if the username already exists in the database
int username_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?";
    int exists = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_int(stmt, 0) > 0) {
            exists = 1;
        }
    }

    sqlite3_finalize(stmt);
    return exists;
}

// Function to register a new user
void register_user(sqlite3 *db, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (username_exists(db, username)) {
        printf("Username already exists.\n");
        return;
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);
    
    char hex_password[2 * SHA256_DIGEST_LENGTH + 1];
    bin_to_hex(hashed_password, SHA256_DIGEST_LENGTH, hex_password);

    const char *sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, hex_password, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
    }
}

int main() {
    const char *db_name = "users.db";
    sqlite3 *db;
    char *err_msg = 0;

    if (sqlite3_open(db_name, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS users (" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "username TEXT UNIQUE NOT NULL," \
        "password TEXT NOT NULL," \
        "first_name TEXT NOT NULL," \
        "last_name TEXT NOT NULL," \
        "email TEXT NOT NULL);";

    if (sqlite3_exec(db, sql_create_table, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    // Sample data for registration
    const char *username = "john_doe";
    const char *password = "secure_password123";
    const char *first_name = "John";
    const char *last_name = "Doe";
    const char *email = "john.doe@example.com";

    register_user(db, username, password, first_name, last_name, email);

    sqlite3_close(db);
    return 0;
}