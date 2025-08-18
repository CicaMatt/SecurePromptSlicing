#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1; // Username found
}

int main() {
    sqlite3 *db;
    char *err_message = 0;
    char username[50], password[50], first_name[50], last_name[50], email[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char sql[1000];

    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%49s", email);

    hash_password(password, hashed_password);

    sprintf(sql, "SELECT * FROM users WHERE username='%s';", username);
    int rc = sqlite3_exec(db, sql, callback, 0, &err_message);

    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        sprintf(sql, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%.*s', '%s', '%s', '%s');",
                username,
                SHA256_DIGEST_LENGTH * 2 + 1, hashed_password,
                first_name, last_name, email);

        rc = sqlite3_exec(db, sql, 0, 0, &err_message);
        if (rc == SQLITE_OK) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "SQL error: %s\n", err_message);
            sqlite3_free(err_message);
        }
    }

    sqlite3_close(db);
    return 0;
}