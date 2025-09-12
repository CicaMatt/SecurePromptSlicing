#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "user.db"
#define USERNAME_LEN 50
#define PASSWORD_LEN 100

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i*2], "%02x", (unsigned int)digest[i]);
    }
}

void insert_user(sqlite3 *db, const char *username, const char *password_hash) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO users (username, password) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password_hash, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User inserted successfully.\n");
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char password_hash[PASSWORD_LEN * 2 + 1];

    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL UNIQUE, password TEXT NOT NULL);";
    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("Enter username: ");
    if (fgets(username, USERNAME_LEN, stdin) == NULL) {
        fprintf(stderr, "Failed to read username.\n");
        sqlite3_close(db);
        return 1;
    }
    // Remove newline character from username
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    if (fgets(password, PASSWORD_LEN, stdin) == NULL) {
        fprintf(stderr, "Failed to read password.\n");
        sqlite3_close(db);
        return 1;
    }
    // Remove newline character from password
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, password_hash);

    insert_user(db, username, password_hash);

    sqlite3_close(db);
    return 0;
}