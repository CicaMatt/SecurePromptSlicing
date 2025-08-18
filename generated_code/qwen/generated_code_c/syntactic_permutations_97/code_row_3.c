#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define MAX_NAME 50
#define MAX_EMAIL 100

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

int register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char create_table_sql[] = "CREATE TABLE IF NOT EXISTS users("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "username TEXT UNIQUE NOT NULL,"
                               "password TEXT NOT NULL,"
                               "first_name TEXT NOT NULL,"
                               "last_name TEXT NOT NULL,"
                               "email TEXT NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    char sql[1024];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s');",
             username, hashed_password, first_name, last_name, email);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc == SQLITE_CONSTRAINT) {
        printf("Username already exists.\n");
    } else if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    } else {
        printf("Registration succeeded.\n");
    }

    sqlite3_close(db);
    return 0;
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char email[MAX_EMAIL];

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

    register_user(username, password, first_name, last_name, email);

    return 0;
}