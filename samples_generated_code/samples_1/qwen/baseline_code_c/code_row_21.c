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

    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int register_user(const char *username, const char *password) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    char sql_insert_user[256];
    snprintf(sql_insert_user, sizeof(sql_insert_user),
             "INSERT INTO users (username, password) VALUES ('%s', '%s');",
             username, hashed_password);

    rc = sqlite3_exec(db, sql_insert_user, 0, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if(register_user(username, password) == 0) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}