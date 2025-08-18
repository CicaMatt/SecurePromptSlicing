#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

void hash_password(const char *password, unsigned char *hashed_password) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("registration.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users("
                                   "username TEXT PRIMARY KEY,"
                                   "hashed_password BLOB,"
                                   "first_name TEXT,"
                                   "last_name TEXT,"
                                   "email TEXT);";
    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    char first_name[MAX_NAME_LENGTH + 1];
    char last_name[MAX_NAME_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];

    printf("Enter Username: ");
    scanf("%50s", username);
    printf("Enter Password: ");
    scanf("%100s", password);
    printf("Enter First Name: ");
    scanf("%50s", first_name);
    printf("Enter Last Name: ");
    scanf("%50s", last_name);
    printf("Enter Email: ");
    scanf("%100s", email);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char *sql_check_username = sqlite3_mprintf(
        "SELECT 1 FROM users WHERE username='%q';",
        username
    );

    int user_exists;
    rc = sqlite3_exec(db, sql_check_username, callback, &user_exists, &zErrMsg);
    sqlite3_free(sql_check_username);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    if (user_exists == 1) {
        printf("Username already exists.\n");
    } else {
        char *sql_insert_user = sqlite3_mprintf(
            "INSERT INTO users (username, hashed_password, first_name, last_name, email)"
            "VALUES ('%q', X'%.*s', '%q', '%q', '%q');",
            username,
            SHA256_DIGEST_LENGTH, hashed_password,
            first_name,
            last_name,
            email
        );

        rc = sqlite3_exec(db, sql_insert_user, callback, 0, &zErrMsg);
        sqlite3_free(sql_insert_user);

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