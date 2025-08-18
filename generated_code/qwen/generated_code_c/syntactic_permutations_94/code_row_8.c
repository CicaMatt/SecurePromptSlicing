#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define DB_NAME "users.db"
#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t salt_size) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, sizeof(*salt), salt_size, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_size, unsigned char *hash) {
    SHA512_CTX sha_ctx;
    SHA512_Init(&sha_ctx);
    SHA512_Update(&sha_ctx, salt, salt_size);
    SHA512_Update(&sha_ctx, password, strlen(password));
    SHA512_Final(hash, &sha_ctx);
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *create_table_sql =
        "CREATE TABLE IF NOT EXISTS users ("
        "   username TEXT PRIMARY KEY,"
        "   salt BLOB,"
        "   hashed_password BLOB"
        ");";
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    char username[256];
    char password[256];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        fprintf(stderr, "Failed to read username\n");
        sqlite3_close(db);
        return 1;
    }
    // Remove newline character from the input
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Failed to read password\n");
        sqlite3_close(db);
        return 1;
    }
    // Remove newline character from the input
    password[strcspn(password, "\n")] = '\0';

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hash[SHA512_DIGEST_LENGTH];
    hash_password(password, salt, SALT_SIZE, hash);

    sqlite3_stmt *stmt;
    const char *insert_sql =
        "INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, salt, SALT_SIZE, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, hash, SHA512_DIGEST_LENGTH, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("User added successfully.\n");

    return 0;
}