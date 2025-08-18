#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, char *output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(output + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS users("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "username TEXT NOT NULL,"
                                 "password TEXT NOT NULL);";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    char hashedPassword[65]; // SHA256 hash is 32 bytes, or 64 hex characters + \0
    hash_password(password, hashedPassword);

    char insertSQL[150];
    snprintf(insertSQL, sizeof(insertSQL), "INSERT INTO users(username, password) VALUES('%s', '%s');", username, hashedPassword);

    rc = sqlite3_exec(db, insertSQL, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to insert data: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    printf("User added successfully!\n");

    sqlite3_close(db);
    return 0;
}