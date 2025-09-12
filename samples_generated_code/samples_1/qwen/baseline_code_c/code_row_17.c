#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define HASH_SIZE SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char hash[HASH_SIZE]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hashed_password[HASH_SIZE];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from the end
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from the end
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hashed_password);

    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT NOT NULL UNIQUE,"
                                   "password BLOB NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char insert_sql[500];
    snprintf(insert_sql, sizeof(insert_sql),
             "INSERT INTO users (username, password) VALUES ('%q', ?);",
             username);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_blob(stmt, 1, hashed_password, HASH_SIZE, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User registered successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}