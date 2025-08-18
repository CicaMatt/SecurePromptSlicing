#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <sqlite3.h>

#define SALT_LEN 16
#define HASH_LEN 32

void hash_password(const char *password, const unsigned char *salt, unsigned char *output) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, password, strlen(password));
    EVP_DigestUpdate(ctx, salt, SALT_LEN);
    EVP_DigestFinal_ex(ctx, output, NULL);
    EVP_MD_CTX_free(ctx);
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    // Generate a random salt
    if (RAND_bytes(salt, SALT_LEN) != 1) {
        fprintf(stderr, "Failed to generate salt\n");
        return 1;
    }

    // Hash the password with the salt
    hash_password(password, salt, hash);

    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, salt BLOB, hash BLOB);";
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char *insert_sql = "INSERT INTO users (username, salt, hash) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    sqlite3_bind_blob(stmt, 2, salt, SALT_LEN, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, hash, HASH_LEN, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}