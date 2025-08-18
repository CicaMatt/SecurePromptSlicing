#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "registration.db"
#define SALT_SIZE 16

void generate_salt(unsigned char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, SALT_SIZE, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    unsigned char pwd_salt[SHA256_BLOCK_SIZE + SALT_SIZE];
    
    memcpy(pwd_salt, password, strlen(password));
    memcpy(pwd_salt + strlen(password), salt, SALT_SIZE);

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, pwd_salt, strlen(password) + SALT_SIZE);
    SHA256_Final(hash, &sha256);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void register_user(const char *username, const char *password) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    unsigned char salt[SALT_SIZE];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char sql[1024];

    generate_salt(salt);
    hash_password(password, salt, hash);

    rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }

    sprintf(sql, "CREATE TABLE IF NOT EXISTS users("
                  "username TEXT PRIMARY KEY,"
                  "password_hash BLOB,"
                  "salt BLOB);");

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sprintf(sql, "INSERT INTO users (username, password_hash, salt) VALUES ('%q', X'%.*s', X'%.*s');",
            username, SHA256_DIGEST_LENGTH * 2 + 1, hash, SALT_SIZE * 2 + 1, salt);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sqlite3_close(db);
}

int main() {
    char username[256], password[256];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    register_user(username, password);

    printf("User registered successfully.\n");

    return 0;
}