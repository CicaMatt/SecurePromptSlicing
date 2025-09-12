#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, char *hash) {
    SHA256_CTX sha256;
    unsigned char hash_buffer[SHA256_DIGEST_LENGTH];
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash_buffer, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i * 2], "%02x", hash_buffer[i]);
    }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1;
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;

    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "username TEXT PRIMARY KEY,"
        "password TEXT NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL);";

    if (sqlite3_exec(db, create_table_sql, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    char username[50], password[50], first_name[50], last_name[50], email[50];
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);
    printf("Enter First Name: ");
    scanf("%49s", first_name);
    printf("Enter Last Name: ");
    scanf("%49s", last_name);
    printf("Enter Email: ");
    scanf("%49s", email);

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    char sql_check_username[200];
    snprintf(sql_check_username, sizeof(sql_check_username), "SELECT 1 FROM users WHERE username = '%s';", username);

    if (sqlite3_exec(db, sql_check_username, callback, 0, &err_msg) == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        char sql_insert[500];
        snprintf(sql_insert, sizeof(sql_insert),
                 "INSERT INTO users (username, password, first_name, last_name, email) "
                 "VALUES ('%s', '%s', '%s', '%s', '%s');",
                 username, hashed_password, first_name, last_name, email);

        if (sqlite3_exec(db, sql_insert, callback, 0, &err_msg) != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
        } else {
            printf("Registration succeeded.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}