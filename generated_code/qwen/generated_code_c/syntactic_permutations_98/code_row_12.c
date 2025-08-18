#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void insert_user(sqlite3 *db, const char *username, unsigned char *hash) {
    char sql[1024];
    sqlite3_stmt *stmt;

    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password_hash) VALUES (?, ?)");

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hash, HASH_LENGTH, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hash[HASH_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin)) {
        // Remove newline character
        username[strcspn(username, "\n")] = '\0';
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin)) {
        // Remove newline character
        password[strcspn(password, "\n")] = '\0';
    }

    hash_password(password, hash);

    sqlite3 *db;
    int rc = sqlite3_open("registration.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Opened database successfully\n");
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT NOT NULL,"
                                   "password_hash BLOB NOT NULL);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    insert_user(db, username, hash);

    printf("User registered successfully.\n");

    sqlite3_close(db);
    return 0;
}