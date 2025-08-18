#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 100

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(digest, &sha_ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)digest[i]);
    }
}

void insert_user(sqlite3 *db, const char *username, const char *password_hash) {
    char sql[512];
    snprintf(sql, sizeof(sql),
             "INSERT INTO users (username, password_hash) VALUES ('%s', '%s');",
             username, password_hash);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_step(stmt);
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
}

int main() {
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, password_hash);

    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT NOT NULL UNIQUE,"
                                   "password_hash TEXT NOT NULL);";

    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    insert_user(db, username, password_hash);

    sqlite3_close(db);
    printf("User inserted successfully.\n");
    return 0;
}