#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"
#define USERNAME_MAX 50
#define PASSWORD_MAX 100
#define EMAIL_MAX 100
#define FIRST_NAME_MAX 50
#define LAST_NAME_MAX 50

void hash_password(const char *password, char *hashed_output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_output + (i * 2), "%02x", digest[i]);
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
        return 1;
    }

    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL"
        ");";

    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    char username[USERNAME_MAX], password[PASSWORD_MAX], hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    char first_name[FIRST_NAME_MAX], last_name[LAST_NAME_MAX], email[EMAIL_MAX];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%99s", password);
    printf("Enter First Name: ");
    scanf("%49s", first_name);
    printf("Enter Last Name: ");
    scanf("%49s", last_name);
    printf("Enter Email: ");
    scanf("%99s", email);

    hash_password(password, hashed_password);

    char sql_check_user[256];
    snprintf(sql_check_user, sizeof(sql_check_user),
             "SELECT * FROM users WHERE username='%q';", username);

    int exists = 0;
    rc = sqlite3_exec(db, sql_check_user, callback, &exists, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    if (exists) {
        printf("Username already exists.\n");
    } else {
        char sql_insert_user[512];
        snprintf(sql_insert_user, sizeof(sql_insert_user),
                 "INSERT INTO users(username, password, first_name, last_name, email)"
                 "VALUES('%q', '%q', '%q', '%q', '%q');",
                 username, hashed_password, first_name, last_name, email);

        rc = sqlite3_exec(db, sql_insert_user, 0, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            sqlite3_close(db);
            return 1;
        }

        printf("Registration succeeded.\n");
    }

    sqlite3_close(db);
    return 0;
}