#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("users.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT NOT NULL,"
                                   "password_hash BLOB NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char password_hash[HASH_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, password_hash);

    sqlite3_stmt *stmt;
    const char *insert_sql = "INSERT INTO users (username, password_hash) VALUES (?, ?);";

    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, password_hash, HASH_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User inserted successfully!\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}