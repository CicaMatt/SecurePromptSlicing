#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 100

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password[i*2], "%02x", hash[i]);
    }
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hashed_password);

    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("registration.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT NOT NULL UNIQUE,"
                                   "password TEXT NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO users (username, password) VALUES ('%q', '%q');",
             username, hashed_password);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to insert data: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("Registration successful!\n");
    }

    sqlite3_close(db);

    return 0;
}