#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define SALT_SIZE 16

void generate_salt(unsigned char* salt, size_t salt_size) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_size, fp);
    fclose(fp);
}

void hash_password(const char* password, const unsigned char* salt, size_t salt_size, unsigned char* hashed_password) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, salt_size);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[SALT_SIZE];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_SIZE);
    hash_password(password, salt, SALT_SIZE, hashed_password);

    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char* create_sql = "CREATE TABLE IF NOT EXISTS users("
                             "username TEXT PRIMARY KEY,"
                             "salt BLOB,"
                             "hashed_password BLOB);";

    rc = sqlite3_exec(db, create_sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char insert_sql[500];
    snprintf(insert_sql, sizeof(insert_sql), 
             "INSERT INTO users(username, salt, hashed_password) VALUES('%q', ?, ?);",
             username);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_blob(stmt, 1, salt, SALT_SIZE, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed_password, SHA256_DIGEST_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}