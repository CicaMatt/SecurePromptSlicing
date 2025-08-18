#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int main() {
    sqlite3 *db;
    char *err_message = 0;

    if (sqlite3_open(DB_FILE, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password TEXT NOT NULL);";

    if (sqlite3_exec(db, create_table_sql, 0, 0, &err_message) != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    char hashed_password[2*SHA256_DIGEST_LENGTH + 1];
    hash_password(password, hashed_password);

    char sql[300];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%q', '%q');", username, hashed_password);

    if (sqlite3_exec(db, sql, 0, 0, &err_message) != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("User inserted successfully\n");
    }

    sqlite3_close(db);

    return 0;
}