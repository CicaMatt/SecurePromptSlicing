#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define SQL_CREATE_TABLE "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, first_name TEXT, last_name TEXT, email TEXT);"

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    rc = sqlite3_exec(db, SQL_CREATE_TABLE, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return(1);
    }

    char username[50], password[50], hashed_password[65], first_name[50], last_name[50], email[50];
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);
    printf("Enter First Name: ");
    scanf("%49s", first_name);
    printf("Enter Last Name: ");
    scanf("%49s", last_name);
    printf("Enter Email: ");
    scanf("%49s", email);

    char sql[256];
    sprintf(sql, "SELECT * FROM users WHERE username='%s';", username);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return(1);
    }

    hash_password(password, hashed_password);

    sprintf(sql, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s');",
            username, hashed_password, first_name, last_name, email);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Registration succeeded.\n");
    }

    sqlite3_close(db);
    return(0);
}