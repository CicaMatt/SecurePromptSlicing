#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define HASH_SIZE 20

typedef struct {
    char username[50];
    unsigned char hashed_password[HASH_SIZE];
    char first_name[50];
    char last_name[50];
    char email[100];
} User;

int callback(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

void hashPassword(const char* password, unsigned char* hashed_password) {
    SHA1((unsigned char*)password, strlen(password), hashed_password);
}

int checkUsernameExists(sqlite3* db, const char* username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM users WHERE username=?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int exists = sqlite3_column_int(stmt, 0) > 0;
    sqlite3_finalize(stmt);
    return exists;
}

int registerUser(sqlite3* db, const User* user) {
    if (checkUsernameExists(db, user->username)) {
        printf("Username already exists.\n");
        return 0;
    }

    char *errMsg = NULL;
    int rc = sqlite3_exec(db, 
        "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);", 
        callback, 
        NULL, 
        &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 0;
    }

    printf("Registration succeeded.\n");
    return 1;
}

int main() {
    sqlite3 *db;
    char *errMsg = NULL;
    
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return EXIT_FAILURE;
    }

    const char* sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password BLOB NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL);";

    rc = sqlite3_exec(db, sqlCreateTable, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    User newUser;
    printf("Enter username: ");
    scanf("%49s", newUser.username);
    printf("Enter password: ");
    scanf("%49s", (char*)newUser.hashed_password);  // Temporarily use hashed_password to store input
    hashPassword(newUser.hashed_password, newUser.hashed_password);

    printf("Enter first name: ");
    scanf("%49s", newUser.first_name);
    printf("Enter last name: ");
    scanf("%49s", newUser.last_name);
    printf("Enter email: ");
    scanf("%99s", newUser.email);

    registerUser(db, &newUser);

    sqlite3_close(db);
    return EXIT_SUCCESS;
}