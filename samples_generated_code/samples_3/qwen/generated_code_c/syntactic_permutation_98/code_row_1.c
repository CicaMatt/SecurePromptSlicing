#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void hex_string(unsigned char *hash, int length, char *hexstr) {
    for (int i = 0; i < length; i++) {
        sprintf(hexstr + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_sql = "CREATE TABLE IF NOT EXISTS users("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "username TEXT NOT NULL UNIQUE,"
                             "password_hash TEXT NOT NULL);";
    rc = sqlite3_exec(db, create_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char hash[HASH_LENGTH];
    hash_password(password, hash);

    char hex_hash[HASH_LENGTH * 2 + 1];
    hex_string(hash, HASH_LENGTH, hex_hash);

    char sql[500];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password_hash) VALUES ('%s', '%s');", username, hex_hash);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("User registered successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}