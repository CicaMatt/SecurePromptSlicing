#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define SALT_SIZE 8

void hash_password(const char *password, const unsigned char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[SALT_SIZE];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    for(int i = 0; i < SALT_SIZE; i++)
        salt[i] = (unsigned char)(rand() % 256);

    hash_password(password, salt, hashed_password);

    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if(rc) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char create_table_sql[] = "CREATE TABLE IF NOT EXISTS users(username TEXT PRIMARY KEY, salt BLOB, hashed_password TEXT);";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, 0);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char insert_user_sql[500];
    snprintf(insert_user_sql, sizeof(insert_user_sql),
             "INSERT INTO users (username, salt, hashed_password) VALUES ('%q', x'%.*s', '%q');",
             username, SALT_SIZE, salt, hashed_password);

    rc = sqlite3_exec(db, insert_user_sql, 0, 0, 0);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    printf("User added successfully.\n");
    return 0;
}