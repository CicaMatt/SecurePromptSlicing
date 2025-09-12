#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int insert_user(sqlite3 *db, const char *username, const unsigned char *hashed_password) {
    char sql[200];
    sprintf(sql, "INSERT INTO users (username, password_hash) VALUES ('%s', X'%s')", username, sqlite3_mprintf("%x", hashed_password, 32));
    char *err_msg = NULL;
    return sqlite3_exec(db, sql, NULL, NULL, &err_msg);
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT UNIQUE, password_hash BLOB);";
    char *err_msg = NULL;
    rc = sqlite3_exec(db, create_table_sql, NULL, NULL, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    rc = insert_user(db, username, hashed_password);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to insert user: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    printf("User registered successfully.\n");

    sqlite3_close(db);
    return 0;
}