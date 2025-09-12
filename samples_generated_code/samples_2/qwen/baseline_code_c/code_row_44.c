#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define SALT "saltySalt123"
#define DB_FILE "users.db"

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char salted_password[256];

    snprintf(salted_password, sizeof(salted_password), "%s%s", password, SALT);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

int insert_user(sqlite3 *db, const char *username, const char *hashed_password) {
    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, hashed_password);

    char *err_message = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        return 1;
    }
    return 0;
}

int main() {
    char username[256];
    char password[256];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, hashed_password);

    sqlite3 *db;
    int rc = sqlite3_open(DB_FILE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char create_table_sql[] = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT);";
    rc = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    insert_user(db, username, hashed_password);

    sqlite3_close(db);
    printf("User added successfully.\n");
    return 0;
}