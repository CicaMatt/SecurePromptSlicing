#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

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

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char* sql_create_table = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL"
        ");";

    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    char username[50], password[50], hashed_password[SHA256_DIGEST_LENGTH*2+1];
    char first_name[50], last_name[50], email[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);
    hash_password(password, hashed_password);

    printf("Enter First Name: ");
    scanf("%49s", first_name);

    printf("Enter Last Name: ");
    scanf("%49s", last_name);

    printf("Enter Email: ");
    scanf("%49s", email);

    char sql_check_username[200];
    snprintf(sql_check_username, sizeof(sql_check_username), 
             "SELECT * FROM users WHERE username = '%q';", username);

    int user_exists;
    rc = sqlite3_exec(db, sql_check_username, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        sqlite3_stmt *stmt;
        const char* tail;

        rc = sqlite3_prepare_v2(db, sql_check_username, -1, &stmt, &tail);
        if (rc == SQLITE_OK) {
            user_exists = sqlite3_step(stmt) == SQLITE_ROW;
            sqlite3_finalize(stmt);
        }
    }

    if (user_exists) {
        printf("Username already exists.\n");
    } else {
        char sql_insert_user[500];
        snprintf(sql_insert_user, sizeof(sql_insert_user), 
                 "INSERT INTO users (username, password, first_name, last_name, email) "
                 "VALUES ('%q', '%q', '%q', '%q', '%q');", 
                 username, hashed_password, first_name, last_name, email);

        rc = sqlite3_exec(db, sql_insert_user, callback, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            printf("Registration succeeded.\n");
        }
    }

    sqlite3_close(db);

    return 0;
}