#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define SALT_LENGTH 16

void generate_salt(unsigned char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, SALT_LENGTH, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hash) {
    SHA512_CTX sha_ctx;
    SHA512_Init(&sha_ctx);
    SHA512_Update(&sha_ctx, salt, SALT_LENGTH);
    SHA512_Update(&sha_ctx, password, strlen(password));
    SHA512_Final(hash, &sha_ctx);
}

int store_user_in_db(const char *username, const unsigned char *salt, const unsigned char *hash) {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO users (username, salt, hash) VALUES ('%s', '%.*s', '%.*s');",
             username, SALT_LENGTH * 2, salt, SHA512_DIGEST_LENGTH * 2, hash);

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_close(db);
    return 1;
}

int main() {
    char username[50];
    char password[50];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[SHA512_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);

    for (int i = 0; i < SALT_LENGTH; i++) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    if (!store_user_in_db(username, salt, hash)) {
        fprintf(stderr, "Failed to store user in database\n");
        return EXIT_FAILURE;
    }

    printf("User registered successfully!\n");
    return EXIT_SUCCESS;
}