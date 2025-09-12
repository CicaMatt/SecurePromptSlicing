#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100
#define HASH_SIZE SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char hash[HASH_SIZE]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
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

    const char *create_table_sql =
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password_hash BLOB NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL"
        ");";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    char first_name[MAX_NAME_LENGTH], last_name[MAX_NAME_LENGTH], email[MAX_EMAIL_LENGTH];
    unsigned char password_hash[HASH_SIZE];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    printf("Enter First Name: ");
    scanf("%s", first_name);

    printf("Enter Last Name: ");
    scanf("%s", last_name);

    printf("Enter Email: ");
    scanf("%s", email);

    hash_password(password, password_hash);

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT COUNT(*) FROM users WHERE username = '%q';",
             username);

    int exists;
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);

    if (exists) {
        printf("Username already exists.\n");
    } else {
        snprintf(sql, sizeof(sql),
                 "INSERT INTO users(username, password_hash, first_name, last_name, email) "
                 "VALUES('%q', ?, '%q', '%q', '%q');",
                 username, first_name, last_name, email);

        sqlite3_stmt *insert_stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &insert_stmt, 0);
        if (rc == SQLITE_OK) {
            sqlite3_bind_blob(insert_stmt, 1, password_hash, HASH_SIZE, SQLITE_STATIC);
            rc = sqlite3_step(insert_stmt);

            if (rc == SQLITE_DONE) {
                printf("Registration succeeded.\n");
            } else {
                fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
            }
        } else {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_finalize(insert_stmt);
    }

    sqlite3_close(db);
    return 0;
}