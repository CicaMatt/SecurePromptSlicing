#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    char username[100];
    char password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);

    char sql[500];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO users (username, password) VALUES ('%q', '%q');",
             username,
             sqlite3_mprintf("%z", sqlite3_hex(hashed_password)));

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_free(sqlite3_mprintf("%z", sqlite3_hex(hashed_password)));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_free(sqlite3_mprintf("%z", sqlite3_hex(hashed_password)));
    sqlite3_close(db);

    printf("User added successfully.\n");
    return 0;
}