#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int create_table(sqlite3 *db) {
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL UNIQUE, "
        "password BLOB NOT NULL);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
        return 1;
    if (sqlite3_step(stmt) != SQLITE_DONE)
        return 1;
    sqlite3_finalize(stmt);
    return 0;
}

int insert_user(sqlite3 *db, const char *username, const char *password) {
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    const char *sql = "INSERT INTO users (username, password) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK)
        return 1;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    sqlite3_bind_blob(stmt, 2, password_hash, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return 1;
    }
    sqlite3_finalize(stmt);
    return 0;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (create_table(db) != 0) {
        fprintf(stderr, "Failed to create table\n");
        sqlite3_close(db);
        return 1;
    }

    char username[256], password[256];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (insert_user(db, username, password) != 0) {
        fprintf(stderr, "Failed to insert user\n");
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}