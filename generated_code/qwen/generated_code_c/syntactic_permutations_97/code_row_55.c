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
        sprintf(&hashed_password[i*2], "%02x", digest[i]);
    }
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char* create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password TEXT NOT NULL,"
        "firstname TEXT NOT NULL,"
        "lastname TEXT NOT NULL,"
        "email TEXT NOT NULL"
        ");";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    char username[50], password[50], hashed_password[65], firstname[50], lastname[50], email[50];

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

    char query[500];
    snprintf(query, sizeof(query),
             "SELECT * FROM users WHERE username = '%s';", username);

    rc = sqlite3_exec(db, query, 0, 0, &zErrMsg);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        snprintf(query, sizeof(query),
                 "INSERT INTO users(username, password, firstname, lastname, email)"
                 "VALUES('%s', '%s', '%s', '%s', '%s');",
                 username, hashed_password, firstname, lastname, email);
        
        rc = sqlite3_exec(db, query, 0, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            printf("Registration successful.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}