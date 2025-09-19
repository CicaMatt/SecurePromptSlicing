#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char *output) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int insert_user(sqlite3 *db, const char *username, const unsigned char *hashed_password) {
    char sql[256];
    sprintf(sql, "INSERT INTO users (username, password) VALUES ('%s', X'%s')", username, sqlite3_mprintf("%x", hashed_password, 32));
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 1;
    }
    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return result == SQLITE_DONE ? 0 : 1;
}

int main() {
    char username[50];
    char password[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, hashed_password);

    sqlite3 *db;
    if (sqlite3_open("users.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password BLOB)";
    if (sqlite3_exec(db, sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (insert_user(db, username, hashed_password)) {
        printf("Failed to insert user.\n");
    } else {
        printf("User inserted successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}