#include <stdio.h>
#include <string.h>
#include <unistd.h> // for crypt function
#include <sqlite3.h>

#define DB_NAME "users.db"
#define TABLE_NAME "users"

int check_username_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return exists;
}

int register_user(sqlite3 *db, const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
        return 1;
    }

    char hashed_password[128];
    strcpy(hashed_password, crypt(password, "salt"));

    const char *sql = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement.\n");
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Failed to insert user.\n");
        return 1;
    }

    sqlite3_finalize(stmt);
    printf("Registration succeeded.\n");
    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users (" \
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT," \
                                   "username TEXT UNIQUE NOT NULL," \
                                   "password TEXT NOT NULL," \
                                   "first_name TEXT NOT NULL," \
                                   "last_name TEXT NOT NULL," \
                                   "email TEXT NOT NULL);";

    if (sqlite3_exec(db, sql_create_table, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Can't create table: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    register_user(db, username, password, first_name, last_name, email);

    sqlite3_close(db);
    return 0;
}