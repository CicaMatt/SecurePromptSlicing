#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int main() {
    sqlite3 *db;
    const char *database = "users.db";
    int rc;

    if (sqlite3_open(database, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS users (" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "username TEXT NOT NULL UNIQUE," \
        "password BLOB NOT NULL);";

    rc = sqlite3_exec(db, sql_create_table, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[50];
    char password[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);

    char *sql_insert = sqlite3_mprintf(
        "INSERT INTO users (username, password) VALUES ('%q', X'%b');",
        username, hashed_password, SHA256_DIGEST_LENGTH * 2
    );

    rc = sqlite3_exec(db, sql_insert, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User registered successfully.\n");
    }

    sqlite3_free(sql_insert);
    sqlite3_close(db);

    return 0;
}