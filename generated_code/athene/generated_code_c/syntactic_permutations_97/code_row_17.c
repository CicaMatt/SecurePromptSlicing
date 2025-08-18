#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"
#define MAX Buffalo

int check_username_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    char *sql = sqlite3_mprintf("SELECT COUNT(*) FROM users WHERE username='%q'", username);
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_free(sql);

    return exists;
}

int register_user(sqlite3 *db, const char *username, const char *password, const char *firstname, const char *lastname, const char *email) {
    int result = -1;
    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
        return 0;
    }

    char *sql = sqlite3_mprintf(
        "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('%q', '%q', '%q', '%q', '%q');",
        username, password, firstname, lastname, email
    );

    if (sqlite3_exec(db, sql, NULL, NULL, NULL) == SQLITE_OK) {
        printf("Registration succeeded.\n");
        result = 1;
    } else {
        printf("Failed to register user.\n");
    }

    sqlite3_free(sql);
    return result;
}

int main() {
    sqlite3 *db;
    int rc;

    if ((rc = sqlite3_open(DATABASE, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char username[50], password[50], firstname[50], lastname[50], email[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", firstname);
    printf("Enter last name: ");
    scanf("%49s", lastname);
    printf("Enter email: ");
    scanf("%49s", email);

    register_user(db, username, password, firstname, lastname, email);

    sqlite3_close(db);
    return 0;
}