#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_PATH "users.db"
#define BUFFER_SIZE 256

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);
}

int is_username_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    char sql[BUFFER_SIZE];

    snprintf(sql, BUFFER_SIZE, "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int register_user(sqlite3 *db, const char *username, unsigned char hashed_password[SHA256_DIGEST_LENGTH], 
                  const char *first_name, const char *last_name, const char *email) {
    sqlite3_stmt *stmt;
    char sql[BUFFER_SIZE];

    snprintf(sql, BUFFER_SIZE, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
             username, hashed_password, first_name, last_name, email);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc == SQLITE_DONE) {
        printf("Registration succeeded.\n");
        return 1;
    } else {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
        return 0;
    }
}

int main() {
    sqlite3 *db;
    char username[BUFFER_SIZE], password[BUFFER_SIZE], first_name[BUFFER_SIZE], last_name[BUFFER_SIZE], email[BUFFER_SIZE];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    if (sqlite3_open(DB_PATH, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                  "username TEXT UNIQUE NOT NULL,"
                                  "password TEXT NOT NULL,"
                                  "first_name TEXT NOT NULL,"
                                  "last_name TEXT NOT NULL,"
                                  "email TEXT NOT NULL);";
    if (sqlite3_exec(db, create_table_sql, callback, 0, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("Enter username: ");
    scanf("%255s", username);

    if (is_username_exists(db, username)) {
        printf("Username already exists.\n");
    } else {
        printf("Enter password: ");
        scanf("%255s", password);

        printf("Enter first name: ");
        scanf("%255s", first_name);

        printf("Enter last name: ");
        scanf("%255s", last_name);

        printf("Enter email: ");
        scanf("%255s", email);

        hash_password(password, hashed_password);
        char *hex_password = (char *)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            sprintf(hex_password + (i * 2), "%02x", hashed_password[i]);
        }
        hex_password[SHA256_DIGEST_LENGTH * 2] = '\0';

        register_user(db, username, hashed_password, first_name, last_name, email);
        free(hex_password);
    }

    sqlite3_close(db);
    return 0;
}