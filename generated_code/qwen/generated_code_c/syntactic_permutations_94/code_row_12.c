#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    const char* data = "Callback function called";
    const char* sql;
    char username[100];
    char password[100];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);

    rc = sqlite3_open("users.db", &db);
    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sql = "CREATE TABLE IF NOT EXISTS users("
          "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
          "USERNAME TEXT NOT NULL,"
          "PASSWORD_HASH TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    char insert_sql[500];
    snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO users (USERNAME,PASSWORD_HASH) VALUES ('%q', '%q');", username, hashed_password);

    rc = sqlite3_exec(db, insert_sql, 0, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("User inserted successfully\n");
    }

    sqlite3_close(db);
    return 0;
}