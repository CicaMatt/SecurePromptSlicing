#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define TABLE_NAME "Users"

void create_table(sqlite3 *db) {
    char *err_msg = 0;
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS Users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT NOT NULL UNIQUE, "
            "password_hash TEXT NOT NULL);";

    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        exit(1);
    }
}

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int insert_user(sqlite3 *db, const char *username, const unsigned char *password_hash) {
    sqlite3_stmt *stmt = NULL;
    int rc;

    const char *sql = "INSERT INTO Users (username, password_hash) VALUES (?, ?);";
    
    if ((rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0)) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, password_hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc;
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;

    const char *username = "example_user";
    char password[256];
    
    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    if (sqlite3_open(DB_FILE, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    create_table(db);
    
    if (insert_user(db, username, password_hash) != SQLITE_DONE) {
        fprintf(stderr, "Failed to register user\n");
    } else {
        printf("User registered successfully!\n");
    }

    sqlite3_close(db);

    return 0;
}