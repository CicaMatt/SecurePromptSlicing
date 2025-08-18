#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_FIRSTNAME_LENGTH 50

void hash_password(const char *password, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char create_sql[] = "CREATE TABLE IF NOT EXISTS users(username TEXT PRIMARY KEY, password BLOB, firstname TEXT);";
    rc = sqlite3_exec(db, create_sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    char firstname[MAX_FIRSTNAME_LENGTH + 1];

    printf("Enter your username: ");
    scanf("%50s", username);

    printf("Enter your password: ");
    scanf("%100s", password);

    printf("Enter your first name: ");
    scanf("%50s", firstname);

    sqlite3_stmt *stmt;
    const char *check_sql = "SELECT 1 FROM users WHERE username = ?;";
    rc = sqlite3_prepare_v2(db, check_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    const char *insert_sql = "INSERT INTO users(username, password, firstname) VALUES (?, ?, ?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed_password, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, firstname, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    printf("Registration succeeded.\n");

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}