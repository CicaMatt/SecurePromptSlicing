#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int login(sqlite3 *db, const char *username, const char *password) {
    char *errMsg = 0;
    sqlite3_stmt *stmt;
    int rc;

    const char *sql = "SELECT password FROM users WHERE username = ?;";
    
    if ((rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL)) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char *db_password = sqlite3_column_text(stmt, 0);
        if (strcmp((const char *)db_password, password) == 0) {
            printf("Login successful! Redirecting to home page...\n");
            return 1;
        }
    }

    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}

int main() {
    sqlite3 *db;
    char *errMsg = 0;

    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL UNIQUE, "
        "password TEXT NOT NULL);";

    if (sqlite3_exec(db, sqlCreateTable, callback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (!login(db, username, password)) {
        printf("Access denied.\n");
    }

    sqlite3_close(db);
    return 0;
}