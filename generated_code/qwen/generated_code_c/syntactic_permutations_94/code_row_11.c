#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password[i*2], "%02x", (unsigned int)digest[i]);
    }
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "username TEXT PRIMARY KEY,"
                                   "password_hash TEXT);";

    rc = sqlite3_exec(db, create_table_sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    char username[100];
    char password[100];
    printf("Enter your username: ");
    scanf("%99s", username);
    printf("Enter your password: ");
    scanf("%99s", password);

    char hashed_password[SHA256_DIGEST_LENGTH*2 + 1];
    hash_password(password, hashed_password);

    char sql[300];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password_hash) VALUES ('%q', '%q');",
             username, hashed_password);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("User inserted successfully\n");
    }

    sqlite3_close(db);
    return 0;
}