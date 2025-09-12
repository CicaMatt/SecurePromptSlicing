#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"

void create_table(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT UNIQUE, password TEXT, first_name TEXT, last_name TEXT, email TEXT);";
    sqlite3_exec(db, sql, NULL, NULL, NULL);
}

unsigned char* hash_password(const char *password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), digest);
    unsigned char *hexdigest = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hexdigest + (i * 2), "%02x", digest[i]);
    }
    return hexdigest;
}

int register_user(sqlite3 *db, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    int rc;
    sqlite3_stmt *stmt;

    // Check if username already exists
    const char *check_sql = "SELECT COUNT(*) FROM users WHERE username = ?;";
    rc = sqlite3_prepare_v2(db, check_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    int exists = 0;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (exists > 0) {
        printf("Username already exists.\n");
        return -1;
    }

    // Hash the password
    unsigned char *hashed_password = hash_password(password);

    // Insert user into database
    const char *insert_sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        free(hashed_password);
        return -1;
    }
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, (const char *)hashed_password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
        free(hashed_password);
        return -1;
    }

    sqlite3_finalize(stmt);
    printf("Registration succeeded.\n");
    free(hashed_password);
    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    create_table(db);

    char username[256], password[256], first_name[256], last_name[256], email[256];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);

    register_user(db, username, password, first_name, last_name, email);

    sqlite3_close(db);
    return 0;
}