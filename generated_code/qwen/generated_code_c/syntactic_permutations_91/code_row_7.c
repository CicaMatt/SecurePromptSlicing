#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i * 2], "%02x", (unsigned int)digest[i]);
    }
}

int insert_user(sqlite3 *db, const char *username, const char *password) {
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, hashed_password);

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
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users (" \
                                   "username TEXT PRIMARY KEY NOT NULL," \
                                   "password TEXT NOT NULL);";
    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (insert_user(db, username, password)) {
        fprintf(stderr, "Failed to insert user\n");
    } else {
        printf("User inserted successfully\n");
    }

    sqlite3_close(db);
    return 0;
}