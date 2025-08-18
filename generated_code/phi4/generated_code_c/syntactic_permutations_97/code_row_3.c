#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_LEN 256

// Function to hash the password using SHA-256
void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

// Callback function for SQLite queries
int callback(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

// Function to check if a username exists in the database
int does_username_exist(sqlite3 *db, const char *username) {
    char sql[MAX_LEN];
    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);
    
    char *errmsg = 0;
    int ret = sqlite3_exec(db, sql, callback, 0, &errmsg);

    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }
    
    char *result;
    sqlite3_get_table(db, sql, &result, 0, NULL, &errmsg);

    int count = atoi(result);
    sqlite3_free_table(result);
    
    return count > 0 ? 1 : 0;
}

// Function to register a new user
int register_user(sqlite3 *db, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (does_username_exist(db, username)) {
        printf("Username already exists.\n");
        return -1;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    char hashed_password[MAX_LEN + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    
    char sql[MAX_LEN];
    snprintf(sql, sizeof(sql),
             "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, hashed_password, first_name, last_name, email);

    char *errmsg = 0;
    if (sqlite3_exec(db, sql, callback, 0, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }
    
    printf("Registration succeeded.\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *errmsg = 0;

    if (sqlite3_open(":memory:", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *create_table_sql = 
        "CREATE TABLE users (" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "username TEXT UNIQUE NOT NULL," \
        "password TEXT NOT NULL," \
        "first_name TEXT NOT NULL," \
        "last_name TEXT NOT NULL," \
        "email TEXT NOT NULL);";

    if (sqlite3_exec(db, create_table_sql, callback, 0, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return -1;
    }

    char username[MAX_LEN];
    char password[MAX_LEN];
    char first_name[MAX_LEN];
    char last_name[MAX_LEN];
    char email[MAX_LEN];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    printf("Enter first name: ");
    scanf("%255s", first_name);

    printf("Enter last name: ");
    scanf("%255s", last_name);

    printf("Enter email: ");
    scanf("%255s", email);

    register_user(db, username, password, first_name, last_name, email);
    
    sqlite3_close(db);
    return 0;
}