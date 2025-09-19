#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "user_data"

void create_table(sqlite3 *db) {
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS user_data ("  \
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"   \
        "USERNAME TEXT NOT NULL,"                 \
        "PASSWORD_HASH BLOB NOT NULL);";
    sqlite3_exec(db, sql, NULL, NULL, NULL);
}

unsigned char* hash_password(const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)password, strlen(password), hash);
    return hash;
}

int insert_user(sqlite3 *db, const char *username, const char *password) {
    unsigned char *hash = hash_password(password);
    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO user_data (USERNAME, PASSWORD_HASH) VALUES ('%s', ?);", username);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_blob(stmt, 1, hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
    
    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return (result == SQLITE_DONE) ? 0 : -1;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    create_table(db);

    char username[256], password[256];
    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);

    if (insert_user(db, username, password) == 0) {
        printf("User registered successfully.\n");
    } else {
        fprintf(stderr, "Failed to register user.\n");
    }

    sqlite3_close(db);
    return 0;
}