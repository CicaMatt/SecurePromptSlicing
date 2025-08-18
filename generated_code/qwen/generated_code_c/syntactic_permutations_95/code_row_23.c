#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LEN; i++) {
        salt[i] = 'a' + rand() % 26;
    }
    salt[SALT_LEN] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char input[PASSWORD_LEN + SALT_LEN + 1];

    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((unsigned char *)input, strlen(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password[i * 2], "%02x", hash[i]);
    }
}

int register_user(const char *username, const char *password) {
    sqlite3 *db;
    char salt[SALT_LEN + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS users("
                "username TEXT PRIMARY KEY,"
                "hashed_password TEXT,"
                "salt TEXT);";
    if (sqlite3_exec(db, sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char insert_sql[256];
    snprintf(insert_sql, sizeof(insert_sql), 
             "INSERT INTO users (username, hashed_password, salt) VALUES ('%s', '%s', '%s');",
             username, hashed_password, salt);

    if (sqlite3_exec(db, insert_sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_close(db);
    return 1;
}

int main() {
    char username[USERNAME_LEN + 1];
    char password[PASSWORD_LEN + 1];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (register_user(username, password)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}