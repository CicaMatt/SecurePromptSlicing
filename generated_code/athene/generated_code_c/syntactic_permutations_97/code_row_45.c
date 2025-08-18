#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"

int hash_password(const char *password, unsigned char **hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password, strlen(password), digest);
    *hashed_password = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
    if (*hashed_password == NULL) return -1;
    memcpy(*hashed_password, digest, SHA256_DIGEST_LENGTH);
    return 0;
}

int user_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM users WHERE username=?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return -1;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    int exists = 0;
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return exists > 0;
}

int register_user(sqlite3 *db, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    unsigned char *hashed_password;
    if (hash_password(password, &hashed_password) != 0) return -1;

    char hexdigest[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hexdigest + (i * 2), "%02x", hashed_password[i]);
    }

    if (user_exists(db, username)) {
        printf("Username already exists.\n");
        free(hashed_password);
        return -1;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)");
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        free(hashed_password);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, hexdigest, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Failed to register user.\n");
        free(hashed_password);
        sqlite3_finalize(stmt);
        return -1;
    }

    printf("Registration succeeded.\n");

    free(hashed_password);
    sqlite3_finalize(stmt);
    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    char sql[] =
        "CREATE TABLE IF NOT EXISTS users ("  \
        "username TEXT PRIMARY KEY,"          \
        "password TEXT NOT NULL,"             \
        "first_name TEXT NOT NULL,"           \
        "last_name TEXT NOT NULL,"            \
        "email TEXT NOT NULL"                 \
        ");";
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    register_user(db, username, password, first_name, last_name, email);

    sqlite3_close(db);
    return 0;
}