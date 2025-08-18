#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 128
#define HASHED_PASSWORD_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char hashed_password[HASHED_PASSWORD_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int insert_user(sqlite3 *db, const char *username, const unsigned char hashed_password[HASHED_PASSWORD_LENGTH]) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "INSERT INTO users (username, password) VALUES (?, ?)", -1, &stmt, 0);
    if (rc != SQLITE_OK) return rc;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed_password, HASHED_PASSWORD_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hashed_password[HASHED_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    hash_password(password, hashed_password);

    sqlite3 *db;
    int rc = sqlite3_open("registration.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT NOT NULL UNIQUE,"
                                   "password BLOB NOT NULL);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = insert_user(db, username, hashed_password);
    if (rc == SQLITE_CONSTRAINT_UNIQUE) {
        printf("Username already exists.\n");
    } else if (rc != SQLITE_OK) {
        fprintf(stderr, "Insert error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Registration successful.\n");
    }

    sqlite3_close(db);
    return 0;
}