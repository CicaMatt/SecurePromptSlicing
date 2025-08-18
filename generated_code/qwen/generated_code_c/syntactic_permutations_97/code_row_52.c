#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i*2], "%02x", digest[i]);
    }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1;
}

int main() {
    sqlite3 *db;
    char sql[1000];
    char username[MAX_USERNAME_LENGTH + 1], password[MAX_PASSWORD_LENGTH + 1];
    char hashed_password[SHA256_DIGEST_LENGTH*2 + 1];
    char first_name[MAX_NAME_LENGTH + 1], last_name[MAX_NAME_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];
    int rc;

    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    printf("Enter username: ");
    scanf("%50s", username);

    sql[0] = '\0';
    snprintf(sql, sizeof(sql), "SELECT * FROM users WHERE username='%q';", username);
    rc = sqlite3_exec(db, sql, callback, 0, 0);

    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
        sqlite3_close(db);
        return 1;
    }

    printf("Enter password: ");
    scanf("%100s", password);

    printf("Enter first name: ");
    scanf("%50s", first_name);

    printf("Enter last name: ");
    scanf("%50s", last_name);

    printf("Enter email: ");
    scanf("%100s", email);

    hash_password(password, hashed_password);

    sql[0] = '\0';
    snprintf(sql, sizeof(sql), 
             "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%q', '%q', '%q', '%q', '%q');",
             username, hashed_password, first_name, last_name, email);

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("Registration successful.\n");
    sqlite3_close(db);

    return 0;
}