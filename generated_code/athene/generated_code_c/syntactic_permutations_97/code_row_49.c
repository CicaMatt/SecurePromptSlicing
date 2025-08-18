#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"

int hash_password(const char *password, unsigned char *output) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(output, &ctx);
    return 1;
}

void print_hashed_password(unsigned char *hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
}

int check_username_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, "SELECT 1 FROM users WHERE username = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int exists = (rc == SQLITE_ROW);
    sqlite3_finalize(stmt);
    return exists;
}

int insert_user(sqlite3 *db, const char *username, unsigned char *hashed_password, const char *first_name, const char *last_name, const char *email) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)");

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    unsigned char hex_string[65];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf((char*)(hex_string + i * 2), "%02x", hashed_password[i]);
    }
    sqlite3_bind_text(stmt, 2, (const char*)hex_string, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int success = (rc == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

int main() {
    sqlite3 *db;
    char username[50], first_name[50], last_name[50], email[100];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);

    char password[50];
    printf("Enter password: ");
    scanf("%s", password);

    if (hash_password(password, password_hash) != 1) {
        printf("Failed to hash password.\n");
        return -1;
    }

    int rc = sqlite3_open(DB_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
        sqlite3_close(db);
        return 0;
    }

    if (insert_user(db, username, password_hash, first_name, last_name, email)) {
        printf("Registration succeeded.\n");
    } else {
        printf("Failed to register user.\n");
    }

    sqlite3_close(db);
    return 0;
}