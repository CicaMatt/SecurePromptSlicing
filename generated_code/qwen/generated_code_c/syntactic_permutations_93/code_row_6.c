#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char* password, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void insert_user(sqlite3* db, const char* username, const unsigned char hash[SHA256_DIGEST_LENGTH]) {
    char sql[512];
    char hashed_password_hex[2 * SHA256_DIGEST_LENGTH + 1];
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password_hex[i*2], "%02x", hash[i]);
    }

    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password_hash) VALUES ('%s', '%s');", username, hashed_password_hex);
    
    char *errmsg;
    int rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
}

int main() {
    const char* username = "example_user";
    const char* password = "example_password";

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL UNIQUE, password_hash TEXT NOT NULL);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    insert_user(db, username, hash);

    sqlite3_close(db);

    return 0;
}