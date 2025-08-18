#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS users(" \
                                   "username TEXT PRIMARY KEY NOT NULL," \
                                   "password TEXT NOT NULL," \
                                   "firstname TEXT NOT NULL," \
                                   "lastname TEXT NOT NULL," \
                                   "email TEXT NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    char username[50], password[50], firstname[50], lastname[50], email[100];
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);
    printf("Enter First Name: ");
    scanf("%49s", firstname);
    printf("Enter Last Name: ");
    scanf("%49s", lastname);
    printf("Enter Email: ");
    scanf("%99s", email);

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    char sql_check[300];
    snprintf(sql_check, sizeof(sql_check), "SELECT 1 FROM users WHERE username='%s';", username);
    rc = sqlite3_exec(db, sql_check, callback, 0, &zErrMsg);

    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        char sql_insert[500];
        snprintf(sql_insert, sizeof(sql_insert), "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('%s', '%s', '%s', '%s', '%s');",
                 username, hashed_password, firstname, lastname, email);

        rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);
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