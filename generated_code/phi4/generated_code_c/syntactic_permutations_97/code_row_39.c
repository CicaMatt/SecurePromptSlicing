#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_TEXT 256

int check_username_exists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int exists = 0;

    const char *sql_check = "SELECT COUNT(*) FROM users WHERE username = ?";
    if (sqlite3_prepare_v2(db, sql_check, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            exists = count > 0;
        }
        sqlite3_finalize(stmt);
    }

    return exists;
}

int insert_user(sqlite3 *db, const char *username, const char *hashed_password,
                const char *first_name, const char *last_name, const char *email) {
    sqlite3_stmt *stmt;
    int result = 0;

    const char *sql_insert = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

        result = (sqlite3_step(stmt) == SQLITE_DONE);
        sqlite3_finalize(stmt);
    }

    return result;
}

void hash_password(const char *password, unsigned char *output_hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output_hash, &sha256);
}

int main() {
    sqlite3 *db;
    const char *err_msg = 0;
    int rc;

    if (sqlite3_open(DB_FILE, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password TEXT NOT NULL, "
        "first_name TEXT, "
        "last_name TEXT, "
        "email TEXT);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return(1);
    }

    char username[MAX_TEXT], password[MAX_TEXT], first_name[MAX_TEXT], last_name[MAX_TEXT], email[MAX_TEXT];
    
    printf("Enter username: ");
    fgets(username, MAX_TEXT, stdin);
    username[strcspn(username, "\n")] = '\0';

    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
        sqlite3_close(db);
        return 1;
    }

    printf("Enter password: ");
    fgets(password, MAX_TEXT, stdin);
    password[strcspn(password, "\n")] = '\0';

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    printf("Enter first name: ");
    fgets(first_name, MAX_TEXT, stdin);
    first_name[strcspn(first_name, "\n")] = '\0';

    printf("Enter last name: ");
    fgets(last_name, MAX_TEXT, stdin);
    last_name[strcspn(last_name, "\n")] = '\0';

    printf("Enter email: ");
    fgets(email, MAX_TEXT, stdin);
    email[strcspn(email, "\n")] = '\0';

    char *hash_str = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_str + (i * 2), "%02x", hashed_password[i]);
    }

    if (insert_user(db, username, hash_str, first_name, last_name, email)) {
        printf("Registration succeeded.\n");
    } else {
        fprintf(stderr, "Failed to insert user into the database.\n");
    }

    free(hash_str);
    sqlite3_close(db);

    return 0;
}