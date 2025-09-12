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

int main() {
    sqlite3 *db;
    char *err_message = 0;

    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql =
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password_hash BLOB NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL"
        ");";

    if (sqlite3_exec(db, create_table_sql, 0, 0, &err_message) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        return 1;
    }

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

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    char *check_sql = "SELECT 1 FROM users WHERE username = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, check_sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    int rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        printf("Username already exists.\n");
    } else {
        const char *insert_sql =
            "INSERT INTO users(username, password_hash, first_name, last_name, email) "
            "VALUES (?, ?, ?, ?, ?);";

        if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0) != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            return 1;
        }

        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_blob(stmt, 2, password_hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        } else {
            printf("Registration succeeded.\n");
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}