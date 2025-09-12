#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, unsigned char *hashed_output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_output, &sha256);
}

void register_user(const char *username, const char *password) {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password_hash BLOB NOT NULL"
        ");";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char *insert_sql = sqlite3_mprintf(
        "INSERT INTO users (username, password_hash) VALUES (?, ?);"
    );

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, hashed_password, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

        rc = sqlite3_step(stmt);

        if (rc != SQLITE_DONE) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        }
    } else {
        fprintf(stderr, "SQL prepare failed: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    const char *username = "testuser";
    const char *password = "securepassword";

    register_user(username, password);

    return 0;
}