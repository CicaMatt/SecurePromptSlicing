#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define SALT_LENGTH 16

void generate_salt(char *salt, size_t salt_length) {
    for (size_t i = 0; i < salt_length; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A');
    }
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void store_user_in_db(const char *username, const unsigned char *hash, const char *salt) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql_create_table =
            "CREATE TABLE IF NOT EXISTS users("
            "username TEXT PRIMARY KEY,"
            "hash BLOB,"
            "salt TEXT"
            ");";
    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *sql_insert_user =
            "INSERT INTO users (username, hash, salt) VALUES (?, ?, ?);";
    rc = sqlite3_prepare_v2(db, sql_insert_user, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, salt, SALT_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char username[100];
    char password[100];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char salt[SALT_LENGTH + 1];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_LENGTH);
    salt[SALT_LENGTH] = '\0';

    hash_password(password, salt, hash);

    store_user_in_db(username, hash, salt);

    printf("User registered successfully!\n");

    return 0;
}