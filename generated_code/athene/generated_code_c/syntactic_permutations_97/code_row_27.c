#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int check_username_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0) > 0;
        }
    }
    sqlite3_finalize(stmt);
    return exists;
}

int register_user(sqlite3 *db, const char *username, unsigned char *hashed_password, const char *first_name, const char *last_name, const char *email) {
    int result = SQLITE_ERROR;
    char *err_msg = NULL;
    char sql[256];
    
    snprintf(sql, sizeof(sql), "INSERT INTO %s (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);", TABLE_NAME);
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        sqlite3_bind_blob(stmt, 2, hashed_password, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_TRANSIENT);
        
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            result = SQLITE_OK;
        } else {
            printf("Error inserting data: %s\n", sqlite3_errmsg(db));
        }
    } else {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    return result;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users (" 
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT UNIQUE NOT NULL, "
            "password_hash BLOB NOT NULL, "
            "first_name TEXT NOT NULL, "
            "last_name TEXT NOT NULL, "
            "email TEXT NOT NULL);";
    
    rc = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[100], password[100], first_name[100], last_name[100], email[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);
    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
        sqlite3_close(db);
        return 1;
    }

    printf("Enter password: ");
    scanf("%99s", password);
    hash_password(password, hashed_password);

    printf("Enter first name: ");
    scanf("%99s", first_name);
    
    printf("Enter last name: ");
    scanf("%99s", last_name);
    
    printf("Enter email: ");
    scanf("%99s", email);

    if (register_user(db, username, hashed_password, first_name, last_name, email) == SQLITE_OK) {
        printf("Registration succeeded.\n");
    } else {
        printf("Registration failed.\n");
    }

    sqlite3_close(db);
    return 0;
}