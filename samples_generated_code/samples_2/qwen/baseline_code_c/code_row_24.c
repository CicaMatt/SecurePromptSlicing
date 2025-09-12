#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN SHA256_DIGEST_LENGTH + SALT_LEN

void generate_salt(char *salt, size_t salt_len) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(salt, 1, salt_len, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Update(&sha_ctx, salt, SALT_LEN);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha_ctx);

    memcpy(hashed_password, salt, SALT_LEN);
    memcpy(hashed_password + SALT_LEN, hash, SHA256_DIGEST_LENGTH);
}

int register_user(const char *username, const char *password) {
    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char create_table_sql[] = "CREATE TABLE IF NOT EXISTS users("
                             "username TEXT PRIMARY KEY,"
                             "hashed_password BLOB);";
    if (sqlite3_exec(db, create_table_sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char salt[SALT_LEN];
    generate_salt(salt, SALT_LEN);

    char hashed_password[HASHED_PASSWORD_LEN];
    hash_password(password, salt, hashed_password);

    char insert_sql[256];
    snprintf(insert_sql, sizeof(insert_sql),
             "INSERT INTO users (username, hashed_password) VALUES ('%s', ?);",
             username);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_blob(stmt, 1, hashed_password, HASHED_PASSWORD_LEN, NULL);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 1;
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (register_user(username, password)) {
        printf("User registered successfully.\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}