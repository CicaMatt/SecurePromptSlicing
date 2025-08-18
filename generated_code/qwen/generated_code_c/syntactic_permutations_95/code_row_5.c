#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN (SHA256_DIGEST_LENGTH * 2 + SALT_LEN)

void generate_salt(unsigned char salt[SALT_LEN]) {
    FILE* urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, SALT_LEN, urandom);
    fclose(urandom);
}

void hash_password(const char* password, const unsigned char salt[SALT_LEN], char hashed_password[HASHED_PASSWORD_LEN]) {
    SHA256_CTX sha256;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    memcpy(hashed_password + (SHA256_DIGEST_LENGTH * 2), salt, SALT_LEN);
}

int register_user(const char* username, const char* password) {
    sqlite3* db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT);";
    rc = sqlite3_exec(db, create_table_sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    unsigned char salt[SALT_LEN];
    generate_salt(salt);

    char hashed_password[HASHED_PASSWORD_LEN];
    hash_password(password, salt, hashed_password);

    char sql[500];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, hashed_password);
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int verify_user(const char* username, const char* password) {
    sqlite3* db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char sql[500];
    snprintf(sql, sizeof(sql), "SELECT password FROM users WHERE username = '%s';", username);

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    int result = 0;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const unsigned char* stored_hashed_password = sqlite3_column_text(stmt, 0);

        unsigned char salt[SALT_LEN];
        memcpy(salt, stored_hashed_password + SHA256_DIGEST_LENGTH * 2, SALT_LEN);

        char hashed_password[HASHED_PASSWORD_LEN];
        hash_password(password, salt, hashed_password);

        if (memcmp(stored_hashed_password, hashed_password, HASHED_PASSWORD_LEN - SALT_LEN) == 0) {
            result = 1;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return result;
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (register_user(username, password) == 0) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
        return EXIT_FAILURE;
    }

    char verify_password[PASSWORD_LEN];
    printf("Enter password to verify: ");
    scanf("%s", verify_password);

    if (verify_user(username, verify_password)) {
        printf("Password verified successfully.\n");
    } else {
        printf("Invalid username or password.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}