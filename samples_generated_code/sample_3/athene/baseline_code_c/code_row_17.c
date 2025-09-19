#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define HASH_SIZE 64

void hash_password(const char *password, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    sqlite3 *db;
    const char *sql;
    char sql_stmt[256];
    char username[100], password[100], hashed_password[HASH_SIZE+1];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, hashed_password);

    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    sql = "CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT);";
    if (sqlite3_exec(db, sql, NULL, 0, &sql) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    snprintf(sql_stmt, sizeof(sql_stmt), 
             "INSERT INTO users (username, password_hash) VALUES ('%s', '%s');",
             username, hashed_password);

    if (sqlite3_exec(db, sql_stmt, NULL, 0, &sql) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User registered successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}