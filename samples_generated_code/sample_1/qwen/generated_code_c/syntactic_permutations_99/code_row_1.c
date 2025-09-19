#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 128

void hash_password(const char *password, unsigned char *digest) {
    SHA512((unsigned char *)password, strlen(password), digest);
}

int main() {
    sqlite3 *db;
    char *err_message = 0;
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    unsigned char hash[SHA512_DIGEST_LENGTH];

    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, hash);

    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%s', '%.*s');",
             username,
             SHA512_DIGEST_LENGTH * 2, // hex representation of the hash
             hash); // This is incorrect. We need to convert hash to hex string

    char hash_hex[SHA512_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        sprintf(&hash_hex[i*2], "%02x", (unsigned int)hash[i]);
    }

    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%s', '%s');",
             username,
             hash_hex);

    if (sqlite3_exec(db, sql, 0, 0, &err_message) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("User inserted successfully\n");
    }

    sqlite3_close(db);
    return 0;
}