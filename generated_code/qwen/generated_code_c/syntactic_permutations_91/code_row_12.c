#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 100

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int insert_user(sqlite3 *db, const char *username, const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    char hash_str[(SHA256_DIGEST_LENGTH * 2) + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        sprintf(&hash_str[i*2], "%02x", (unsigned int)hash[i]);

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users(username, password_hash) VALUES('%s', '%s');", username, hash_str);

    char *err_message = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        return 1;
    }

    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT NOT NULL UNIQUE,"
                                   "password_hash TEXT NOT NULL);";

    char *err_message;
    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        exit(1);
    }

    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    if (insert_user(db, username, password)) {
        fprintf(stderr, "Failed to insert user\n");
    } else {
        fprintf(stdout, "User inserted successfully\n");
    }

    sqlite3_close(db);
    return 0;
}