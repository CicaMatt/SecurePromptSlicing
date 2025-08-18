#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100

void hash_password(const char *password, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

void insert_user(sqlite3 *db, const char *username, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    char sql[512];
    sqlite3_stmt *stmt;
    
    sprintf(sql, "INSERT INTO users (username, password) VALUES (?, ?);");
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed_password, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    sqlite3 *db;
    int rc;
    
    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%99s", password);
    
    hash_password(password, hashed_password);
    
    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    const char *create_sql = "CREATE TABLE IF NOT EXISTS users("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "username TEXT NOT NULL UNIQUE,"
                             "password BLOB NOT NULL);";
                             
    if (sqlite3_exec(db, create_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    insert_user(db, username, hashed_password);
    
    sqlite3_close(db);
    return 0;
}