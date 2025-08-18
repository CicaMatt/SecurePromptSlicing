#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <sqlite3.h>

#define SALT_SIZE 16
#define HASH_SIZE EVP_MAX_MD_SIZE
#define USERNAME_SIZE 50
#define PASSWORD_SIZE 50

void hash_password(const char *password, const unsigned char *salt, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned int md_len;

    md = EVP_sha256();
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestUpdate(mdctx, salt, SALT_SIZE);
    EVP_DigestFinal_ex(mdctx, output, &md_len);
    EVP_MD_CTX_free(mdctx);
}

int main() {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    unsigned char salt[SALT_SIZE], hash[HASH_SIZE];
    sqlite3 *db;
    int rc;

    printf("Enter username: ");
    fgets(username, USERNAME_SIZE, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    fgets(password, PASSWORD_SIZE, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline

    if (RAND_bytes(salt, SALT_SIZE) != 1) {
        fprintf(stderr, "Error generating random salt\n");
        return 1;
    }

    hash_password(password, salt, hash);

    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, hash BLOB);";
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char insert_sql[256];
    snprintf(insert_sql, sizeof(insert_sql), 
             "INSERT INTO users (username, salt, hash) VALUES ('%s', ?, ?);",
             username);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_blob(stmt, 1, salt, SALT_SIZE, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hash, HASH_SIZE, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("User registered successfully.\n");
    return 0;
}