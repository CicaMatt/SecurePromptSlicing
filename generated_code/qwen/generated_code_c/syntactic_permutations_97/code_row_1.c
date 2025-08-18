#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, char *dst) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(dst + (i * 2), "%02x", hash[i]);
    }
    dst[SHA256_DIGEST_LENGTH * 2] = '\0';
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1; // Username exists
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS users (" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "username TEXT UNIQUE NOT NULL," \
        "password TEXT NOT NULL," \
        "first_name TEXT NOT NULL," \
        "last_name TEXT NOT NULL," \
        "email TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return;
    }

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    char sql_check_username[256];
    snprintf(sql_check_username, sizeof(sql_check_username),
             "SELECT 1 FROM users WHERE username = '%s';", username);

    int user_exists;
    rc = sqlite3_exec(db, sql_check_username, callback, &user_exists, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return;
    }

    if (user_exists) {
        printf("Username already exists.\n");
        sqlite3_close(db);
        return;
    }

    char sql_insert_user[512];
    snprintf(sql_insert_user, sizeof(sql_insert_user),
             "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s');",
             username, hashed_password, first_name, last_name, email);

    rc = sqlite3_exec(db, sql_insert_user, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("Registration succeeded.\n");
    }

    sqlite3_close(db);
}

int main() {
    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    printf("Enter First Name: ");
    scanf("%49s", first_name);

    printf("Enter Last Name: ");
    scanf("%49s", last_name);

    printf("Enter Email: ");
    scanf("%99s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}