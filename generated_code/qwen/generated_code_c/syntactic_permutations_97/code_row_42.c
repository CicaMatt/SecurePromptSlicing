#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 100
#define HASH_SIZE SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int check_username_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT 1 FROM users WHERE username = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);

    int exists = (rc == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

void insert_user(sqlite3 *db, const char *username, const unsigned char *hash) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "INSERT INTO users (username, password_hash) VALUES (?, ?)", -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hash, HASH_SIZE, SQLITE_STATIC);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

int main() {
    char username[MAX_USERNAME_LEN], password[MAX_PASSWORD_LEN];
    unsigned char password_hash[HASH_SIZE];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    hash_password(password, password_hash);

    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char create_table_sql[] = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password_hash BLOB NOT NULL);";

    if (sqlite3_exec(db, create_table_sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
    } else {
        insert_user(db, username, password_hash);
        printf("Registration succeeded.\n");
    }

    sqlite3_close(db);
    return 0;
}