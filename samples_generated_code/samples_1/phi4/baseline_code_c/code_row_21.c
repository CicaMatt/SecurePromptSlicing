#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/evp.h>

#define DB_NAME "users.db"
#define SALT_SIZE 16

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void create_table(sqlite3 *db) {
    char *errMsg = NULL;
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password_hash BLOB NOT NULL);";

    int rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        handle_error("Failed to create table");
    }
}

void hash_password(const char *password, unsigned char **hash, unsigned int *len) {
    const EVP_MD *md = EVP_sha256();
    unsigned char salt[SALT_SIZE];
    RAND_bytes(salt, SALT_SIZE);

    if (!EVP_DigestInit_ex(NULL, md, NULL)) handle_error("Digest init failed");
    if (!EVP_DigestUpdate(NULL, salt, SALT_SIZE)) handle_error("Salt update failed");

    size_t hash_size = EVP_MD_size(md) + SALT_SIZE;
    *hash = malloc(hash_size);

    memcpy(*hash, salt, SALT_SIZE);
    if (!EVP_DigestUpdate(NULL, password, strlen(password))) handle_error("Password update failed");
    if (!EVP_DigestFinal_ex(NULL, (*hash) + SALT_SIZE, len)) handle_error("Digest final failed");

    *len += SALT_SIZE;
}

int insert_user(sqlite3 *db, const char *username, unsigned char *password_hash, unsigned int len) {
    sqlite3_stmt *stmt = NULL;
    const char *sql = "INSERT INTO users (username, password_hash) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        handle_error("Failed to prepare statement");
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, password_hash, len, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        handle_error("Failed to insert user");
    }

    sqlite3_finalize(stmt);
    return rc;
}

int main() {
    sqlite3 *db;
    char *errMsg = NULL;

    if (sqlite3_open(DB_NAME, &db)) {
        handle_error("Can't open database");
    }

    create_table(db);

    const char *username = "testuser";
    unsigned char *password_hash = NULL;
    unsigned int hash_len = 0;

    printf("Enter username: ");
    scanf("%ms", &username);
    
    char password[256];
    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, &password_hash, &hash_len);

    insert_user(db, username, password_hash, hash_len);

    free(password_hash);
    sqlite3_close(db);
    return 0;
}