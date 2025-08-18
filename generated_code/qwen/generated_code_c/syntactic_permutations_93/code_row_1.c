#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int insert_user(sqlite3 *db, const char *username, const unsigned char *hashed_password) {
    sqlite3_stmt *stmt;
    int rc;

    const char *sql = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) return rc;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed_password, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

int main() {
    char username[50];
    char password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    sqlite3 *db;
    int rc;

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);

    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL, password_hash BLOB NOT NULL);";
    rc = sqlite3_exec(db, create_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = insert_user(db, username, hashed_password);
    if (rc == SQLITE_OK) {
        printf("User added successfully.\n");
    } else {
        fprintf(stderr, "Insert error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);

    return 0;
}