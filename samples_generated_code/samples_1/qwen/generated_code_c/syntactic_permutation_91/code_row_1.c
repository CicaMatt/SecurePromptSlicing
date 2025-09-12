#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DATABASE "users.db"

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(digest, &sha_ctx);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int register_user(const char *name, const char *password) {
    sqlite3 *db;
    char sql[512];
    char hashed_password[65]; // SHA-256 hash is 64 characters long + null terminator

    if (sqlite3_open(DATABASE, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    hash_password(password, hashed_password);

    snprintf(sql, sizeof(sql), "INSERT INTO users (name, password) VALUES ('%q', '%q');", name, hashed_password);
    
    char *err_message = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int main() {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open(DATABASE, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, password TEXT NOT NULL);";
    char *err_message = 0;

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        return 1;
    }

    char name[256];
    char password[256];

    printf("Enter your name: ");
    scanf("%255s", name);

    printf("Enter your password: ");
    scanf("%255s", password);

    if (register_user(name, password) == 0) {
        printf("User registered successfully!\n");
    } else {
        printf("Failed to register user.\n");
    }

    sqlite3_close(db);
    return 0;
}