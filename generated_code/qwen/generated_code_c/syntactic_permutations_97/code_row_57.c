#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

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
    return 1; // Indicates that a row was found
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

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS users("
                                   "username TEXT PRIMARY KEY, "
                                   "password TEXT, "
                                   "first_name TEXT, "
                                   "last_name TEXT, "
                                   "email TEXT);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;

    printf("Enter First Name: ");
    fgets(first_name, MAX_NAME_LENGTH, stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Enter Last Name: ");
    fgets(last_name, MAX_NAME_LENGTH, stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter Email: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = 0;

    hash_password(password, hashed_password);

    char *check_username_sql = sqlite3_mprintf("SELECT 1 FROM users WHERE username='%q';", username);
    int exists = sqlite3_exec(db, check_username_sql, callback, 0, &zErrMsg);
    sqlite3_free(check_username_sql);

    if (exists == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        char *insert_user_sql = sqlite3_mprintf(
            "INSERT INTO users(username, password, first_name, last_name, email) "
            "VALUES('%q', '%q', '%q', '%q', '%q');",
            username, hashed_password, first_name, last_name, email
        );

        rc = sqlite3_exec(db, insert_user_sql, 0, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            printf("Registration successful.\n");
        }
        sqlite3_free(insert_user_sql);
    }

    sqlite3_close(db);
    return 0;
}