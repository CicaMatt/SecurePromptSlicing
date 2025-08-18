#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_EMAIL_LENGTH 100
#define MAX_NAME_LENGTH 50

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("registration.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_sql = "CREATE TABLE IF NOT EXISTS users("
                             "username TEXT PRIMARY KEY,"
                             "password TEXT,"
                             "first_name TEXT,"
                             "last_name TEXT,"
                             "email TEXT);";
    rc = sqlite3_exec(db, create_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    char first_name[MAX_NAME_LENGTH], last_name[MAX_NAME_LENGTH], email[MAX_EMAIL_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    hash_password(password, hashed_password);

    char *check_sql = sqlite3_mprintf("SELECT 1 FROM users WHERE username='%q';", username);
    rc = sqlite3_exec(db, check_sql, 0, 0, &err_message);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else if (rc == SQLITE_DONE) {
        char *insert_sql = sqlite3_mprintf(
            "INSERT INTO users(username, password, first_name, last_name, email)"
            "VALUES('%q', '%q', '%q', '%q', '%q');",
            username, hashed_password, first_name, last_name, email);
        rc = sqlite3_exec(db, insert_sql, 0, 0, &err_message);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_message);
            sqlite3_free(err_message);
            sqlite3_close(db);
            return 1;
        }
        printf("Registration succeeded.\n");
    } else {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_free(check_sql);
    sqlite3_close(db);

    return 0;
}