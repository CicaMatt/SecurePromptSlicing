#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_FIRSTNAME_LENGTH 50
#define MAX_LASTNAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int check_user_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int result = 0;

    if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM users WHERE username=?;", -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return result;
}

int insert_user(sqlite3 *db, const char *username, const char *hashed_password, const char *first_name, const char *last_name, const char *email) {
    int rc = sqlite3_exec(db, "BEGIN;", 0, 0, 0);

    if (rc == SQLITE_OK) {
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);", -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

            rc = sqlite3_step(stmt);
            if (rc == SQLITE_DONE) {
                rc = sqlite3_exec(db, "COMMIT;", 0, 0, 0);
            } else {
                sqlite3_exec(db, "ROLLBACK;", 0, 0, 0);
            }
        }

        sqlite3_finalize(stmt);
    }

    return rc;
}

int main() {
    sqlite3 *db;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char first_name[MAX_FIRSTNAME_LENGTH];
    char last_name[MAX_LASTNAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    if (sqlite3_open(DB_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS users ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "username TEXT UNIQUE NOT NULL,"
                                   "password TEXT NOT NULL,"
                                   "first_name TEXT NOT NULL,"
                                   "last_name TEXT NOT NULL,"
                                   "email TEXT NOT NULL);";

    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    printf("Enter username: ");
    scanf("%49s", username);

    if (check_user_exists(db, username)) {
        printf("Username already exists.\n");
    } else {
        printf("Enter password: ");
        scanf("%99s", password);
        hash_password(password, hashed_password);

        printf("Enter first name: ");
        scanf("%49s", first_name);

        printf("Enter last name: ");
        scanf("%49s", last_name);

        printf("Enter email: ");
        scanf("%99s", email);

        if (insert_user(db, username, hashed_password, first_name, last_name, email) == SQLITE_OK) {
            printf("Registration succeeded.\n");
        } else {
            printf("Registration failed.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}