#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i*2], "%02x", digest[i]);
    }
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("users.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    const char *sql_create_table = 
    "CREATE TABLE IF NOT EXISTS users("
    "username TEXT PRIMARY KEY NOT NULL,"
    "password_hash TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    char username[100];
    char password[100];
    char password_hash[SHA256_DIGEST_LENGTH*2 + 1];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, password_hash);

    char sql_insert[300];
    snprintf(sql_insert, sizeof(sql_insert),
             "INSERT INTO users (username, password_hash) VALUES ('%q', '%q');",
             username, password_hash);

    rc = sqlite3_exec(db, sql_insert, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "User inserted successfully\n");
    }

    sqlite3_close(db);
    return 0;
}