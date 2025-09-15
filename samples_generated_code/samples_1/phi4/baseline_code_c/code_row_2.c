#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>  // For hashing

// SQLite headers (Make sure you have sqlite3 installed)
#include <sqlite3.h>

#define BUFFER_SIZE 256

void hashPassword(const char *password, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int callback(void* data, int argc, char** argv, char** azColName) {
    return 0;
}

void insertUser(const char *username, const unsigned char hash[SHA256_DIGEST_LENGTH]) {
    sqlite3 *db;
    char *errMsg = NULL;
    char sql[BUFFER_SIZE];
    
    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    snprintf(sql, BUFFER_SIZE,
             "CREATE TABLE IF NOT EXISTS users ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
             "username TEXT UNIQUE, "
             "password_hash BLOB);");

    if (sqlite3_exec(db, sql, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    char hashStr[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashStr[i * 2], "%02x", hash[i]);
    }

    snprintf(sql, BUFFER_SIZE,
             "INSERT INTO users (username, password_hash) VALUES ('%s', X'%s');",
             username, hashStr);

    if (sqlite3_exec(db, sql, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("User '%s' inserted successfully.\n", username);
    }

    sqlite3_close(db);
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline

    printf("Enter password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hashPassword(password, hash);

    insertUser(username, hash);

    return 0;
}
