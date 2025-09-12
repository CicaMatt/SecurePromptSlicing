#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i * 2], "%02x", digest[i]);
    }
}

int main() {
    char username[100];
    char password[100];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);

    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql;
    sql = "CREATE TABLE IF NOT EXISTS users("
          "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
          "USERNAME TEXT NOT NULL,"
          "PASSWORD TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char insert_sql[256];
    snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO users (USERNAME, PASSWORD) VALUES ('%s', '%s');",
             username, hashed_password);

    rc = sqlite3_exec(db, insert_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    return 0;
}