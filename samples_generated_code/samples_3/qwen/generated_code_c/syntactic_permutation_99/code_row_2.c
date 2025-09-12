#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
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

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, hashed_password);

    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "CREATE TABLE IF NOT EXISTS users(username TEXT PRIMARY KEY, password TEXT);"
             "INSERT INTO users (username, password) VALUES ('%s', '%s');",
             username, hashed_password);

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("User added successfully.\n");

    sqlite3_close(db);
    return 0;
}