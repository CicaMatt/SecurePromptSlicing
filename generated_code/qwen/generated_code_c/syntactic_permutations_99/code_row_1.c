#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int main() {
    sqlite3 *db;
    char *err_message = 0;

    if(sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS users ("
                                 "username TEXT NOT NULL,"
                                 "password TEXT NOT NULL);";

    if(sqlite3_exec(db, createTableSQL, 0, 0, &err_message) != SQLITE_OK ) {
        fprintf(stderr, "Failed to create table: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return(1);
    }

    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashedPassword);

    char insertSQL[200];
    snprintf(insertSQL, sizeof(insertSQL), "INSERT INTO users (username, password) VALUES ('%q', '%q');", username, hashedPassword);

    if(sqlite3_exec(db, insertSQL, 0, 0, &err_message) != SQLITE_OK ) {
        fprintf(stderr, "Failed to insert data: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("Data inserted successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}