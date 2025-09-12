#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)digest[i]);
    }
}

void insert_user(sqlite3 *db, const char *username, const char *password_hash) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, password_hash);
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

int main() {
    char username[100];
    char password[100];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, password_hash);

    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    insert_user(db, username, password_hash);

    sqlite3_close(db);
    return 0;
}