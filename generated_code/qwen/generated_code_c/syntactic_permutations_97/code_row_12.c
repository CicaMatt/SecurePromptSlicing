#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

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

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(azColName[i], "username") == 0 && argv[i] != NULL) {
            printf("Username already exists.\n");
            return 1;
        }
    }
    return 0;
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT UNIQUE, "
                                   "first_name TEXT, "
                                   "last_name TEXT, "
                                   "email TEXT, "
                                   "password_hash TEXT);";

    const char *sql_check_username = "SELECT username FROM users WHERE username=?;";

    const char *sql_insert_user = "INSERT INTO users(username, first_name, last_name, email, password_hash) VALUES(?,?,?,?,?);";

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    char username[50], first_name[50], last_name[50], email[100], password[50], hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter First Name: ");
    scanf("%49s", first_name);
    printf("Enter Last Name: ");
    scanf("%49s", last_name);
    printf("Enter Email: ");
    scanf("%99s", email);
    printf("Enter Password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);

    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql_check_username, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    int step = sqlite3_step(stmt);
    if (step == SQLITE_ROW) {
        callback(0, 1, &username, (char *[]){"username"});
    } else if (step == SQLITE_DONE) {
        sqlite3_finalize(stmt);

        rc = sqlite3_prepare_v2(db, sql_insert_user, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }

        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, email, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, hashed_password, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}