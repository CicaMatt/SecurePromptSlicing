#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"
#define TABLE_NAME "users"
#define USERNAME_LEN 50
#define PASSWORD_LEN 128
#define NAME_LEN 50
#define EMAIL_LEN 100

void hash_password(const char *password, unsigned char *hashed_password) {
    SHA256((const unsigned char *)password, strlen(password), hashed_password);
}

int check_username_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    char query[256];
    sprintf(query, "SELECT COUNT(*) FROM %s WHERE username = '%s';", TABLE_NAME, username);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return exists;
}

int register_user(sqlite3 *db, const char *username, const unsigned char *hashed_password, const char *first_name, const char *last_name, const char *email) {
    int rc;
    char query[1024];
    sprintf(query, "INSERT INTO %s (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s');",
            TABLE_NAME, username, hashed_password, first_name, last_name, email);

    rc = sqlite3_exec(db, query, NULL, NULL, NULL);
    return (rc == SQLITE_OK);
}

int main() {
    char username[USERNAME_LEN], password[PASSWORD_LEN], first_name[NAME_LEN], last_name[NAME_LEN], email[EMAIL_LEN];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    if (check_username_exists(NULL, username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%s", password);
    hash_password(password, hashed_password);

    printf("Enter first name: ");
    scanf("%s", first_name);

    printf("Enter last name: ");
    scanf("%s", last_name);

    printf("Enter email: ");
    scanf("%s", email);

    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char create_table_query[256];
    sprintf(create_table_query, "CREATE TABLE IF NOT EXISTS %s (username TEXT PRIMARY KEY, password TEXT, first_name TEXT, last_name TEXT, email TEXT);", TABLE_NAME);
    if (sqlite3_exec(db, create_table_query, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (register_user(db, username, hashed_password, first_name, last_name, email)) {
        printf("User registered successfully.\n");
    } else {
        fprintf(stderr, "Failed to register user.\n");
    }

    sqlite3_close(db);
    return 0;
}