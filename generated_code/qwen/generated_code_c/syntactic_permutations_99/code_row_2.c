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
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i*2], "%02x", (unsigned int)digest[i]);
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
        return(0);
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users (" \
                                  "username TEXT PRIMARY KEY," \
                                  "password_hash TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    char username[100];
    char password[100];
    printf("Enter your username: ");
    scanf("%99s", username);
    printf("Enter your password: ");
    scanf("%99s", password);

    char hashed_password[SHA256_DIGEST_LENGTH*2 + 1];
    hash_password(password, hashed_password);

    char sql_insert_user[300];
    snprintf(sql_insert_user, sizeof(sql_insert_user),
             "INSERT INTO users (username, password_hash) VALUES ('%q', '%q');",
             username, hashed_password);

    rc = sqlite3_exec(db, sql_insert_user, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "User inserted successfully\n");
    }

    sqlite3_close(db);
    return 0;
}