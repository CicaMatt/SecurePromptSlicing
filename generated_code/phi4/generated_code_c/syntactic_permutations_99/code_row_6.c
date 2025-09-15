#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "credentials"

void create_table();
void insert_user(const char *username, const unsigned char hash[SHA256_DIGEST_LENGTH]);
unsigned char* hash_password(const char *password);
int execute_sql(const char *query);

int main() {
    const char *username = "user1";
    const char *password = "securePassword123";

    create_table();

    unsigned char *hashed_password = hash_password(password);
    insert_user(username, hashed_password);

    free(hashed_password);
    return 0;
}

unsigned char* hash_password(const char *password) {
    unsigned char *hash = malloc(SHA256_DIGEST_LENGTH);
    if (!hash) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    return hash;
}

void create_table() {
    const char *sql = "CREATE TABLE IF NOT EXISTS credentials (id INTEGER PRIMARY KEY, username TEXT UNIQUE, password_hash BLOB);";
    if (!execute_sql(sql)) {
        fprintf(stderr, "Failed to create table\n");
        exit(1);
    }
}

void insert_user(const char *username, const unsigned char hash[SHA256_DIGEST_LENGTH]) {
    char *hash_str = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (!hash_str) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hash_str + (i * 2), "%02x", hash[i]);
    }
    
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO credentials (username, password_hash) VALUES ('%s', X'%s');", username, hash_str);
    
    if (!execute_sql(query)) {
        fprintf(stderr, "Failed to insert user\n");
    }

    free(hash_str);
}

int execute_sql(const char *query) {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char *err_msg = NULL;

    rc = sqlite3_exec(db, query, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_close(db);
    return 1;
}
