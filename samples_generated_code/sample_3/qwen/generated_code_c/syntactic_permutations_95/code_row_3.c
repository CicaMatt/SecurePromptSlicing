#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH + SALT_LEN)

void generate_salt(char *salt, int length) {
    for (int i = 0; i < length; i++) {
        salt[i] = 'A' + rand() % 26;
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    strcpy(hashed_password + (SHA256_DIGEST_LENGTH * 2), salt);
}

int register_user(const char *username, const char *password) {
    sqlite3 *db;
    char sql[256];
    char salt[SALT_LEN + 1];
    char hashed_password[HASHED_PASSWORD_LEN + 1];

    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hashed_password);

    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%q', '%q');",
             username, hashed_password);

    sqlite3_exec(db, sql, 0, 0, 0);
    sqlite3_close(db);
    return 1;
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (register_user(username, password)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}