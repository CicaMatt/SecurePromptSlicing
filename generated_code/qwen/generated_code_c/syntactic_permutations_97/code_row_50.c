#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1; // Return 1 to indicate that a row was found
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Check if the username already exists
    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s';", username);

    int row_exists = 0;
    rc = sqlite3_exec(db, query, callback, &row_exists, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    if (row_exists) {
        printf("Username already exists.\n");
        sqlite3_close(db);
        return;
    }

    // Hash the password
    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    // Insert new user into the database
    char insert_query[512];
    snprintf(insert_query, sizeof(insert_query),
             "INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s');",
             username,
             hash,
             first_name,
             last_name,
             email);

    rc = sqlite3_exec(db, insert_query, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    printf("Registration succeeded.\n");
    sqlite3_close(db);
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Initialize the database and create users table if it doesn't exist
    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password_hash BLOB NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL);";

    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    // Get user input
    char username[50], password[50], first_name[50], last_name[50], email[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%49s", email);

    // Register the user
    register_user(username, password, first_name, last_name, email);

    return 0;
}