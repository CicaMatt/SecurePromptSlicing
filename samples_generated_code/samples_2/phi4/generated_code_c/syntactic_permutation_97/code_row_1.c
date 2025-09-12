#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_INPUT_SIZE 256

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void hashPassword(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);
}

int checkUsernameExists(sqlite3* db, const char* username) {
    sqlite3_stmt *stmt;
    int exists = 0;

    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            exists = (count > 0) ? 1 : 0;
        }
    }

    sqlite3_finalize(stmt);
    return exists;
}

int insertUser(sqlite3* db, const char* username, const unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO users (username, password) VALUES (?, ?)";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, hashed, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return (result == SQLITE_DONE) ? 1 : 0;
    }

    return 0;
}

int main() {
    sqlite3 *db;
    char username[MAX_INPUT_SIZE], firstName[MAX_INPUT_SIZE], lastName[MAX_INPUT_SIZE], email[MAX_INPUT_SIZE];
    unsigned char hashed[SHA256_DIGEST_LENGTH];

    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS users ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "username TEXT UNIQUE NOT NULL, "
                "password BLOB NOT NULL);";
    
    if (sqlite3_exec(db, sql, callback, 0, &sql) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("Enter username: ");
    scanf("%255s", username);

    if (checkUsernameExists(db, username)) {
        printf("Username already exists.\n");
    } else {
        hashPassword(username, hashed);
        if (insertUser(db, username, hashed)) {
            printf("Registration succeeded!\n");
        } else {
            fprintf(stderr, "Could not insert user into database.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}


**Note:** This code requires the OpenSSL library to be installed for hashing and SQLite3 for database operations. You need to link against these libraries when compiling:


gcc -o registration registration.c -lsqlite3 -lcrypto