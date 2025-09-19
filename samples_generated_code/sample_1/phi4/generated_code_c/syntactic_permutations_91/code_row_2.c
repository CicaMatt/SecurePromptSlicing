#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms)*1000)
#endif

#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int callback(void *data, int argc, char **argv, char **azColName) {
    return 0; // Not used in this example
}

void initialize_database(sqlite3 **db) {
    char *err_msg = NULL;
    int rc;

    rc = sqlite3_open("users.db", db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        exit(1);
    }

    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password_hash BLOB NOT NULL);";

    rc = sqlite3_exec(*db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(*db);
        exit(1);
    }
}

void register_user(sqlite3 *db, const char *username, unsigned char password_hash[SHA256_DIGEST_LENGTH]) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO users (username, password_hash) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, password_hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Error inserting data: %s\n", sqlite3_errmsg(db));
        }
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

void close_database(sqlite3 *db) {
    if (sqlite3_close(db)) {
        fprintf(stderr, "Cannot close database: %s\n", sqlite3_errmsg(db));
    }
}

int main() {
    sqlite3 *db;
    
    initialize_database(&db);

    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    register_user(db, username, password_hash);

    printf("Registration successful!\n");

    close_database(db);

    return 0;
}
