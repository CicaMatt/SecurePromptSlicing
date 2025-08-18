#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

int hash_password(const char *password, unsigned char **hashed_password) {
    *hashed_password = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
    if (*hashed_password == NULL) return -1;
    SHA256((const unsigned char *)password, strlen(password), *hashed_password);
    return 0;
}

int insert_user(sqlite3 *db, const char *username, const unsigned char *hashed_password) {
    char sql[256];
    int rc;

    snprintf(sql, sizeof(sql),
             "INSERT INTO users (username, password_hash) VALUES ('%s', X'%s');",
             username, sqlite3_mprintf("%x", hashed_password, SHA256_DIGEST_LENGTH));

    rc = sqlite3_exec(db, sql, NULL, 0, NULL);
    if (rc != SQLITE_OK) return -1;
    return 0;
}

int main() {
    sqlite3 *db;
    char username[50];
    char password[50];
    unsigned char *hashed_password;

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (hash_password(password, &hashed_password) != 0) {
        fprintf(stderr, "Error hashing password\n");
        return -1;
    }

    if (sqlite3_open("users.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        free(hashed_password);
        return -1;
    }

    char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "username TEXT PRIMARY KEY,"
        "password_hash BLOB);";
    
    if (sqlite3_exec(db, create_table_sql, NULL, 0, NULL) != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        free(hashed_password);
        sqlite3_close(db);
        return -1;
    }

    if (insert_user(db, username, hashed_password) != 0) {
        fprintf(stderr, "Error inserting user: %s\n", sqlite3_errmsg(db));
        free(hashed_password);
        sqlite3_close(db);
        return -1;
    }

    printf("User successfully registered.\n");

    free(hashed_password);
    sqlite3_close(db);

    return 0;
}