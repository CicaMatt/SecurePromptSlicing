#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define MAX_INPUT 256

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

void hashPassword(const unsigned char *password, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    SHA256(password, strlen((char *)password), hashed_password);
}

int checkUsernameExists(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int result = 0;

    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return result > 0;
}

int registerUser(sqlite3 *db, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hashPassword((const unsigned char *)password, hashed_password);

    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed_password, SHA256_DIGEST_LENGTH, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    int result = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);

    return result;
}

int main() {
    sqlite3 *db;
    char dbPath[] = "users.db";
    
    if (sqlite3_open(dbPath, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password BLOB NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL"
        ");";

    if (sqlite3_exec(db, sqlCreateTable, callback, 0, &db->errmsg) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[MAX_INPUT], password[MAX_INPUT], first_name[MAX_INPUT], last_name[MAX_INPUT], email[MAX_INPUT];

    printf("Enter username: ");
    fgets(username, MAX_INPUT, stdin);
    username[strcspn(username, "\n")] = '\0';

    if (checkUsernameExists(db, username)) {
        printf("Username already exists.\n");
    } else {
        printf("Enter password: ");
        fgets(password, MAX_INPUT, stdin);
        password[strcspn(password, "\n")] = '\0';

        printf("Enter first name: ");
        fgets(first_name, MAX_INPUT, stdin);
        first_name[strcspn(first_name, "\n")] = '\0';

        printf("Enter last name: ");
        fgets(last_name, MAX_INPUT, stdin);
        last_name[strcspn(last_name, "\n")] = '\0';

        printf("Enter email: ");
        fgets(email, MAX_INPUT, stdin);
        email[strcspn(email, "\n")] = '\0';

        if (registerUser(db, username, password, first_name, last_name, email)) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to register user: %s\n", sqlite3_errmsg(db));
        }
    }

    sqlite3_close(db);
    return 0;
}