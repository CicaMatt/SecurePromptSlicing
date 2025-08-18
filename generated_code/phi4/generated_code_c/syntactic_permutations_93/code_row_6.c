#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

// Function to hash a password using SHA-256
unsigned char* hash_password(const char *password, int *length) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char *digest;

    md = EVP_sha256();
    if (!(mdctx = EVP_MD_CTX_new())) return NULL;

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) goto err;
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) goto err;
    if (1 != EVP_DigestFinal_ex(mdctx, NULL, length)) goto err;

    digest = (unsigned char*)malloc(*length);
    if (!digest) goto err;

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) goto err;
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) goto err;
    if (1 != EVP_DigestFinal_ex(mdctx, digest, length)) goto err;

    EVP_MD_CTX_free(mdctx);
    return digest;
err:
    EVP_MD_CTX_free(mdctx);
    return NULL;
}

// Function to insert username and hashed password into the database
int insert_user(const char *username, const unsigned char *hashed_password, int hash_length) {
    // Example using SQLite3 (assuming sqlite3 library is installed)
    #include <sqlite3.h>

    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // Create table if not exists
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password BLOB NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return rc;
    }

    // Insert new user
    char *stmt = NULL;
    char password_hex[2 * EVP_MD_size(EVP_sha256()) + 1];
    for (int i = 0; i < hash_length; ++i) {
        sprintf(password_hex + 2 * i, "%02x", hashed_password[i]);
    }

    snprintf(sql, sizeof(sql), 
             "INSERT INTO users (username, password) VALUES ('%s', X'%s');",
             sqlite3_mprintf(username),
             password_hex);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // Clean up
    sqlite3_free(stmt);
    sqlite3_close(db);

    return rc;
}

int main() {
    char username[256];
    char password[256];

    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);

    int length;
    unsigned char *hashed_password = hash_password(password, &length);
    if (!hashed_password) {
        fprintf(stderr, "Error hashing password\n");
        return 1;
    }

    if (insert_user(username, hashed_password, length) != SQLITE_OK) {
        fprintf(stderr, "Error inserting user into database\n");
    } else {
        printf("User inserted successfully.\n");
    }

    free(hashed_password);
    return 0;
}