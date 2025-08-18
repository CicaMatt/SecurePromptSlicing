#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1;
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, first_name TEXT, last_name TEXT, email TEXT);";
    rc = sqlite3_exec(db, create_table_sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), "SELECT 1 FROM users WHERE username = '%q';", username);

    int user_exists = 0;
    rc = sqlite3_exec(db, sql, callback, &user_exists, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    }

    if (user_exists) {
        printf("Username already exists.\n");
    } else {
        char hashed_password[65]; // 2 * SHA256_DIGEST_LENGTH + 1
        hash_password(password, hashed_password);

        snprintf(sql, sizeof(sql), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%q', '%q', '%q', '%q', '%q');",
                 username, hashed_password, first_name, last_name, email);

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            printf("Registration succeeded.\n");
        }
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