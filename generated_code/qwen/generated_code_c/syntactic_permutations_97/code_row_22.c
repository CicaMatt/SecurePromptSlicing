#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    const char* username = "testuser";
    const char* password = "password123";
    const char* first_name = "John";
    const char* last_name = "Doe";
    const char* email = "john.doe@example.com";

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "username TEXT PRIMARY KEY,"
                                   "password TEXT,"
                                   "first_name TEXT,"
                                   "last_name TEXT,"
                                   "email TEXT);";

    rc = sqlite3_exec(db, create_table_sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    char check_username_sql[256];
    snprintf(check_username_sql, sizeof(check_username_sql), "SELECT username FROM users WHERE username='%s';", username);

    rc = sqlite3_exec(db, check_username_sql, callback, 0, &zErrMsg);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        char insert_user_sql[512];
        snprintf(insert_user_sql, sizeof(insert_user_sql),
                 "INSERT INTO users (username, password, first_name, last_name, email)"
                 "VALUES ('%s', '%s', '%s', '%s', '%s');",
                 username, hashed_password, first_name, last_name, email);

        rc = sqlite3_exec(db, insert_user_sql, callback, 0, &zErrMsg);
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