#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_SIZE 8

void generate_salt(unsigned char *salt, size_t salt_size) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_size, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_size, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, salt_size);
    SHA256_Final(hash, &sha256);
}

void store_user_in_db(const char *username, const unsigned char *hashed_password_with_salt, size_t hashed_password_length) {
    sqlite3 *db;
    int rc = sqlite3_open("registration.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }

    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO users (username, hashed_password_with_salt) VALUES ('%s', ?);",
             username);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_bind_blob(stmt, 1, hashed_password_with_salt, hashed_password_length, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hashed_password_with_salt[SHA256_DIGEST_LENGTH + SALT_SIZE];
    memcpy(hashed_password_with_salt, salt, SALT_SIZE);
    hash_password(password, salt, SALT_SIZE, hashed_password_with_salt + SALT_SIZE);

    store_user_in_db(username, hashed_password_with_salt, sizeof(hashed_password_with_salt));

    printf("User registered successfully.\n");

    return 0;
}