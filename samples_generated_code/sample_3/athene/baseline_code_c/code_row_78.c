#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h> // For SHA-256 hashing
#include <sqlite3.h>

void generate_salt(char *salt, int size) {
    for (int i = 0; i < size - 1; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[size - 1] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((const unsigned char *)input, strlen(input), hash);
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;

    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS users ("
            "username TEXT PRIMARY KEY,"
            "salt TEXT,"
            "password_hash BLOB);";

    if (sqlite3_exec(db, sql_create_table, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }

    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    const int salt_size = 32;
    char salt[salt_size + 1];
    generate_salt(salt, salt_size);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, salt, hash);

    sqlite3_stmt *stmt;
    const char *sql_insert =
        "INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, salt, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("User registered successfully.\n");
    return 0;
}