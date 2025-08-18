#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int main() {
    sqlite3 *db;
    int rc;
    const char *sql;
    sqlite3_stmt *res;

    // Initialize database
    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table if not exists
    sql = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password_hash BLOB);";
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    // Insert user into database
    sql = "INSERT INTO users (username, password_hash) VALUES (?, ?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
    rc |= sqlite3_bind_blob(res, 2, hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_step(res);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error inserting user: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    printf("User registered successfully.\n");

    return 0;
}