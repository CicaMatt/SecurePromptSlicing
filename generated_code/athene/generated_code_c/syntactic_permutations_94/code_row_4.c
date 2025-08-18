#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, SALT_SIZE, 1, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    unsigned char salted_pass[256];
    snprintf((char *)salted_pass, sizeof(salted_pass), "%s%s", password, salt);
    SHA256((const unsigned char *)salted_pass, strlen((const char *)salted_pass), hash);
}

int main() {
    sqlite3 *db;
    int rc;
    const char *sql;
    char username[100];
    char password[100];
    char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];

    // Initialize database
    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create table if not exists
    sql = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password_hash BLOB, salt BLOB);";
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Get username and password from user
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    // Generate salt and hash password
    generate_salt(salt);
    hash_password(password, salt, hash);

    // Insert into database
    char *err_msg = 0;
    sql = "INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hash, HASH_SIZE, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, salt, SALT_SIZE, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", err_msg ? err_msg : sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("User registered successfully.\n");
    return 0;
}