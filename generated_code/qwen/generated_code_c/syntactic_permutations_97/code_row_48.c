#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define MAX_FIRSTNAME 50
#define MAX_LASTNAME 50
#define MAX_EMAIL 100

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

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    const char* sql_create_table = "CREATE TABLE IF NOT EXISTS users("
                                   "username TEXT PRIMARY KEY,"
                                   "password TEXT NOT NULL,"
                                   "firstname TEXT NOT NULL,"
                                   "lastname TEXT NOT NULL,"
                                   "email TEXT NOT NULL);";

    rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Table created successfully.\n");
    }

    char username[MAX_USERNAME], password[MAX_PASSWORD], hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    char firstname[MAX_FIRSTNAME], lastname[MAX_LASTNAME], email[MAX_EMAIL];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Enter First Name: ");
    scanf("%s", firstname);
    printf("Enter Last Name: ");
    scanf("%s", lastname);
    printf("Enter Email: ");
    scanf("%s", email);

    hash_password(password, hashed_password);

    char query[1024];
    snprintf(query, sizeof(query), "SELECT 1 FROM users WHERE username = '%s';", username);
    rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);

    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        snprintf(query, sizeof(query),
                 "INSERT INTO users (username, password, firstname, lastname, email)"
                 "VALUES ('%s', '%s', '%s', '%s', '%s');",
                 username, hashed_password, firstname, lastname, email);

        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            printf("Registration succeeded.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}