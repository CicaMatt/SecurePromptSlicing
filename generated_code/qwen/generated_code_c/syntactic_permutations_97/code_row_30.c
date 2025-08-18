#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 128
#define MAX_FIRSTNAME_LENGTH 50
#define MAX_LASTNAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

int check_username_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM users WHERE username = ?;", -1, &stmt, 0);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_step(stmt);

    int exists = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return exists;
}

void register_user(sqlite3 *db, const char *username, const char *password, 
                   const char *firstname, const char *lastname, const char *email) {
    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
        return;
    }

    char hashed_password[MAX_PASSWORD_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, 
        "INSERT INTO users (username, password, firstname, lastname, email) VALUES (?, ?, ?, ?, ?);", -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, firstname, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, lastname, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        printf("Registration succeeded.\n");
    } else {
        printf("Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password TEXT NOT NULL,"
        "firstname TEXT,"
        "lastname TEXT,"
        "email TEXT"
        ");";
    
    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    char firstname[MAX_FIRSTNAME_LENGTH + 1];
    char lastname[MAX_LASTNAME_LENGTH + 1];
    char email[MAX_EMAIL_LENGTH + 1];

    printf("Enter Username: ");
    scanf("%50s", username);
    printf("Enter Password: ");
    scanf("%128s", password);
    printf("Enter First Name: ");
    scanf("%50s", firstname);
    printf("Enter Last Name: ");
    scanf("%50s", lastname);
    printf("Enter Email: ");
    scanf("%100s", email);

    register_user(db, username, password, firstname, lastname, email);

    sqlite3_close(db);
    return 0;
}