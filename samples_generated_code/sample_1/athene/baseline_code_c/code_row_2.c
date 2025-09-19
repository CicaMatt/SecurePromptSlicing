#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int insert_user(sqlite3 *db, const char *username, const unsigned char *password_hash) {
    char sql[256];
    sprintf(sql, "INSERT INTO users (username, password_hash) VALUES ('%s', X'%s')", username, sqlite3_mprintf("%X", password_hash, SHA256_DIGEST_LENGTH));
    char *err_msg = 0;
    return sqlite3_exec(db, sql, 0, 0, &err_msg);
}

int main() {
    const int hash_len = SHA256_DIGEST_LENGTH;
    unsigned char password_hash[hash_len];
    char username[100], password[100];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, password_hash);

    sqlite3 *db;
    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char create_table_sql[] = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL,"
        "password_hash BLOB NOT NULL);";

    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int result = insert_user(db, username, password_hash);

    if (result == SQLITE_OK) {
        printf("User registered successfully.\n");
    } else {
        fprintf(stderr, "Failed to register user: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);
    return 0;
}