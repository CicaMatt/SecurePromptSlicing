#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_SIZE, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char salted_password[256];
    int i;
    for (i = 0; password[i] != '\0'; ++i)
        salted_password[i] = password[i];
    for (int j = 0; j < SALT_SIZE; ++j)
        salted_password[i + j] = salt[j];
    
    SHA256(salted_password, i + SALT_SIZE, output);
}

int main() {
    char username[100], password[100];
    char salt[SALT_SIZE];
    unsigned char hashed_password[HASH_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO users (username, salt, password_hash) VALUES ('%s', X'%s', X'%s');",
             username, sqlite3_mprintf("%x", salt, SALT_SIZE),
             sqlite3_mprintf("%x", hashed_password, HASH_SIZE));

    char *zErrMsg = 0;
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("User registered successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}