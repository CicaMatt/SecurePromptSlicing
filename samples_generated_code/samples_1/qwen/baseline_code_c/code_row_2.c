#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 128
#define HASHED_PASSWORD_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char hash[HASHED_PASSWORD_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hashed_password[HASHED_PASSWORD_LENGTH];
    sqlite3 *db;
    int rc;

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%127s", password);

    hash_password(password, hashed_password);

    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO users (username, password) VALUES ('%q', X'%.*s');",
             username, HASHED_PASSWORD_LENGTH * 2, hashed_password);

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    printf("User added successfully.\n");
    return 0;
}