#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 256

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), hashed);
}

int username_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT 1 FROM users WHERE username = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int exists = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return exists;
}

int insert_user(sqlite3 *db, const char *username, const unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int success = (rc == SQLITE_DONE);

    sqlite3_finalize(stmt);
    return success;
}

void create_table(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "username TEXT UNIQUE NOT NULL, "
                      "password_hash BLOB NOT NULL)";
    
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

void register_user(sqlite3 *db, const char *username, const char *password) {
    unsigned char hashed[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed);

    if (username_exists(db, username)) {
        printf("Username already exists.\n");
    } else {
        if (insert_user(db, username, hashed)) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Error inserting user into database.\n");
        }
    }
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    create_table(db);

    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);

    register_user(db, username, password);

    sqlite3_close(db);
    return 0;
}