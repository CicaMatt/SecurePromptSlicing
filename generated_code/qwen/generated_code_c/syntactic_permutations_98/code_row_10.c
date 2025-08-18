#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100

void hash_password(const char *password, unsigned char *hashed_password) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int register_user(const char *username, const unsigned char *hashed_password) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("users.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql),
             "INSERT INTO users (username, password) VALUES ('%s', '%.*s');",
             username,
             SHA256_DIGEST_LENGTH * 2, hashed_password);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

void print_hex(const unsigned char *buffer, size_t len) {
    for (size_t i = 0; i < len; ++i)
        printf("%02x", buffer[i]);
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    if (fgets(username, MAX_USERNAME_LENGTH, stdin) != NULL) {
        username[strcspn(username, "\n")] = '\0';
    }

    printf("Enter Password: ");
    if (fgets(password, MAX_PASSWORD_LENGTH, stdin) != NULL) {
        password[strcspn(password, "\n")] = '\0';
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    printf("Hashed Password: ");
    print_hex(hashed_password, SHA256_DIGEST_LENGTH);

    if (register_user(username, hashed_password) == 0) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}