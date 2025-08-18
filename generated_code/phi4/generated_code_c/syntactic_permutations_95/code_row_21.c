#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sqlite3.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t salt_size) {
    if (RAND_bytes(salt, salt_size) != 1) {
        fprintf(stderr, "Error generating random bytes\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char **hash_out) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();
    unsigned int md_len;

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating EVP_MD_CTX\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "Error initializing digest context\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating digest with salt\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password))) {
        fprintf(stderr, "Error updating digest with password\n");
        exit(EXIT_FAILURE);
    }

    *hash_out = malloc(EVP_MD_size(md));
    if (!*hash_out) {
        fprintf(stderr, "Memory allocation failed\n");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, *hash_out, &md_len)) {
        fprintf(stderr, "Error finalizing digest\n");
        free(*hash_out);
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
    return md_len;
}

int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void register_user(sqlite3 *db, const char *username, const unsigned char *password) {
    unsigned char salt[SALT_SIZE];
    unsigned char *hash = NULL;
    int hash_len;
    char sql[512];

    generate_salt(salt, SALT_SIZE);
    hash_len = hash_password(password, salt, &hash);

    snprintf(sql, sizeof(sql),
             "INSERT INTO users (username, password_hash, salt) VALUES ('%s', X'%.*s', X'%.*s')",
             username,
             2 * hash_len, hash,
             2 * SALT_SIZE, salt);

    if (sqlite3_exec(db, sql, callback, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        free(hash);
        return;
    }

    printf("User registered successfully.\n");
    free(hash);
}

void create_table(sqlite3 *db) {
    char *errMsg = 0;
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password_hash BLOB NOT NULL,"
        "salt BLOB NOT NULL);";

    if (sqlite3_exec(db, sql, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Table created successfully.\n");
    }
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;

    if (sqlite3_open(":memory:", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    create_table(db);

    const char *username = "testuser";
    const unsigned char password[] = "password123";

    register_user(db, username, password);

    sqlite3_close(db);
    return 0;
}