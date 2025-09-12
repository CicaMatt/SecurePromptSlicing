#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i*2], "%02x", digest[i]);
    }
}

int register_user(const char *username, const char *password) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char hashed_password[MAX_PASSWORD_LENGTH*2 + 1];
    hash_password(password, hashed_password);

    char sql[500];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO users (username, password) VALUES ('%s', '%s');", 
             username, hashed_password);

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    if (register_user(username, password)) {
        printf("Registration failed.\n");
    } else {
        printf("Registration successful.\n");
    }

    return 0;
}