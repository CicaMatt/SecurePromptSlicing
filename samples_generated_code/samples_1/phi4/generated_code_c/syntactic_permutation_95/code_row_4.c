#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>
#include <time.h>

#define DB_NAME "users.db"
#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t salt_size) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Error opening /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_size, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *output_hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Final(output_hash, &sha256);
}

void create_table(sqlite3 *db) {
    char *err_msg = 0;
    const char *sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "username TEXT UNIQUE NOT NULL,"
                      "password_hash BLOB NOT NULL);";

    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        exit(EXIT_FAILURE);
    }
}

int register_user(sqlite3 *db, const char *username, const unsigned char *password_hash, const unsigned char *salt) {
    char *err_msg = 0;
    const char *sql = "INSERT INTO users (username, password_hash) VALUES (?, ?);";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, strlen(username), SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, password_hash, SHA256_DIGEST_LENGTH + SALT_SIZE, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    return 1;
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    create_table(db);

    char username[100];
    unsigned char password_hash[SHA256_DIGEST_LENGTH + SALT_SIZE];
    unsigned char salt[SALT_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);
    getchar(); // consume newline

    printf("Enter password: ");
    char *password = (char *)malloc(256 * sizeof(char));
    fgets(password, 256, stdin);
    size_t len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    generate_salt(salt, SALT_SIZE);
    hash_password(password, salt, password_hash);

    memcpy(password_hash + SHA256_DIGEST_LENGTH, salt, SALT_SIZE);

    if (register_user(db, username, password_hash, salt)) {
        printf("Registration successful!\n");
    } else {
        printf("Registration failed.\n");
    }

    free(password);
    sqlite3_close(db);
    return 0;
}