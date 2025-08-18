#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define USERNAME_MAX 50
#define NAME_MAX 50
#define EMAIL_MAX 100

int check_username_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    char sql[256];
    sprintf(sql, "SELECT COUNT(*) FROM users WHERE username='%s';", username);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return exists;
}

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int register_user(sqlite3 *db, const char *username, const char *first_name, const char *last_name, const char *email, const char *hashed_password) {
    char sql[512];
    sprintf(sql, "INSERT INTO users (username, first_name, last_name, email, password_hash) VALUES ('%s', '%s', '%s', '%s', '%s');", 
            username, first_name, last_name, email, hashed_password);
    return sqlite3_exec(db, sql, NULL, 0, NULL);
}

int main() {
    char username[USERNAME_MAX];
    char first_name[NAME_MAX];
    char last_name[NAME_MAX];
    char email[EMAIL_MAX];
    char password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char hex_hashed_password[2 * SHA256_DIGEST_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter password: ");
    scanf("%s", password);

    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
        sqlite3_close(db);
        return 1;
    }

    hash_password(password, hashed_password);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hex_hashed_password[i * 2], "%02x", (unsigned int)hashed_password[i]);
    }

    if (register_user(db, username, first_name, last_name, email, hex_hashed_password)) {
        printf("Registration succeeded.\n");
    } else {
        printf("Failed to register user.\n");
    }

    sqlite3_close(db);
    return 0;
}