#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Function to hash password with salt using SHA-256
void hash_password(const char *password, unsigned char **salt, unsigned char **hash) {
    const int SALT_LENGTH = 16;
    const int HASH_LENGTH = EVP_MAX_MD_SIZE;

    // Generate random salt
    *salt = (unsigned char *)malloc(SALT_LENGTH);
    if (!RAND_bytes(*salt, SALT_LENGTH)) {
        fprintf(stderr, "Error generating salt\n");
        exit(1);
    }

    // Prepare to hash the password with the salt using SHA-256
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();
    mdctx = EVP_MD_CTX_new();
    if (EVP_DigestInit_ex(mdctx, md, NULL) <= 0) {
        fprintf(stderr, "Error initializing digest context\n");
        exit(1);
    }
    if (EVP_DigestUpdate(mdctx, *salt, SALT_LENGTH) <= 0) {
        fprintf(stderr, "Error updating digest with salt\n");
        exit(1);
    }
    if (EVP_DigestUpdate(mdctx, password, strlen(password)) <= 0) {
        fprintf(stderr, "Error updating digest with password\n");
        exit(1);
    }
    *hash = (unsigned char *)malloc(HASH_LENGTH);
    unsigned int hash_len;
    if (EVP_DigestFinal_ex(mdctx, *hash, &hash_len) <= 0) {
        fprintf(stderr, "Error finalizing digest\n");
        exit(1);
    }

    EVP_MD_CTX_free(mdctx);
}

// Callback function for SQLite
static int callback(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

int main() {
    sqlite3 *db;
    char *err_msg = NULL;

    // Open database connection
    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return EXIT_FAILURE;
    }

    // Create table for storing user data
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS users (" \
        "username TEXT PRIMARY KEY," \
        "salt BLOB," \
        "hashed_password BLOB);";
    
    if (sqlite3_exec(db, sql_create_table, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    // Get username and password from user
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char *salt, *hash;
    hash_password(password, &salt, &hash);

    // Insert the user data into the database
    const char *sql_insert =
        "INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?);";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, salt, sizeof(*salt), SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, hash, strlen((char *)hash), SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Free allocated memory
    free(salt);
    free(hash);

    printf("User registered successfully!\n");
    return EXIT_SUCCESS;
}