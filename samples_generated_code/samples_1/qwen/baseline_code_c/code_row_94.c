#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100

void hash_password(const char *password, unsigned char *digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
}

void insert_user(const char *username, const unsigned char *hashed_password) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("registration.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS users("
        "username TEXT PRIMARY KEY,"
        "password TEXT"
        ");";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return;
    }

    char hashed_password_hex[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password_hex[i*2], "%02x", hashed_password[i]);
    }

    char sql_insert_user[256];
    snprintf(sql_insert_user, sizeof(sql_insert_user),
             "INSERT INTO users (username, password) VALUES ('%s', '%s');",
             username, hashed_password_hex);

    rc = sqlite3_exec(db, sql_insert_user, 0, 0, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return;
    }

    sqlite3_close(db);
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];

    printf("Enter Username: ");
    scanf("%50s", username);

    printf("Enter Password: ");
    scanf("%100s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    insert_user(username, hashed_password);

    return 0;
}