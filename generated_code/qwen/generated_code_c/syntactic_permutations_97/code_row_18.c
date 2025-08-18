#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 100
#define EMAIL_LENGTH 100
#define NAME_LENGTH 50

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
    char *err_message = 0;

    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users("
        "username TEXT PRIMARY KEY,"
        "password TEXT NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL);";

    if (sqlite3_exec(db, create_table_sql, callback, 0, &err_message) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        return 1;
    }

    char username[USERNAME_LENGTH], password[PASSWORD_LENGTH], hashed_password[PASSWORD_LENGTH*2+1];
    char first_name[NAME_LENGTH], last_name[NAME_LENGTH], email[EMAIL_LENGTH];

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

    char query[500];
    snprintf(query, sizeof(query),
             "SELECT * FROM users WHERE username='%s';",
             username);

    int rc = sqlite3_exec(db, query, callback, 0, &err_message);
    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        snprintf(query, sizeof(query),
                 "INSERT INTO users(username, password, first_name, last_name, email)"
                 "VALUES('%s', '%s', '%s', '%s', '%s');",
                 username, hashed_password, first_name, last_name, email);

        rc = sqlite3_exec(db, query, 0, 0, &err_message);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_message);
            sqlite3_free(err_message);
        } else {
            printf("Registration succeeded.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}