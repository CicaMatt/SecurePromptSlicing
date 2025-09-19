#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "registration.db"
#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 16

void generate_salt(unsigned char salt[SALT_LEN]) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, SALT_LEN, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char salt[SALT_LEN], char hashed_password[PASSWORD_LEN]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

void store_user_in_db(const char *username, const char *hashed_password) {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "CREATE TABLE IF NOT EXISTS users(username TEXT PRIMARY KEY, password TEXT);");
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    snprintf(sql, sizeof(sql), "INSERT INTO users(username, password) VALUES('%q', '%q');", username, hashed_password);
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    char hashed_password[PASSWORD_LEN * 2 + SALT_LEN * 2];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    for (int i = 0; i < SALT_LEN; i++) {
        sprintf(hashed_password + PASSWORD_LEN + (i * 2), "%02x", salt[i]);
    }

    store_user_in_db(username, hashed_password);

    printf("User registered successfully!\n");

    return 0;
}