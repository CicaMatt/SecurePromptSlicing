#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)digest[i]);
    }
}

int check_user_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    }

    sqlite3_finalize(stmt);
    return -1;
}

int insert_user(sqlite3 *db, const char *username, const char *hashed_password, const char *first_name, const char *last_name, const char *email) {
    const char *sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);
    printf("Enter Email: ");
    scanf("%s", email);

    hash_password(password, hashed_password);

    sqlite3 *db;
    if (sqlite3_open("users.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT UNIQUE NOT NULL,"
                                   "password TEXT NOT NULL,"
                                   "first_name TEXT NOT NULL,"
                                   "last_name TEXT NOT NULL,"
                                   "email TEXT NOT NULL);";

    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int user_exists = check_user_exists(db, username);
    if (user_exists == -1) {
        fprintf(stderr, "Error checking if user exists.\n");
        sqlite3_close(db);
        return 1;
    } else if (user_exists) {
        printf("User already exists.\n");
        sqlite3_close(db);
        return 0;
    }

    int insert_result = insert_user(db, username, hashed_password, first_name, last_name, email);
    if (insert_result == -1) {
        fprintf(stderr, "Failed to register user.\n");
    } else {
        printf("Registration succeeded.\n");
    }

    sqlite3_close(db);
    return 0;
}