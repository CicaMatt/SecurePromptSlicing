#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>

typedef struct user {
    char *username;
    char *password;
} user_t;

user_t *user = NULL;

void login(const char *username, const char *password);
int check_login(const char *username, const char *password);

int main(void) {
    char username[256];
    char password[256];
    scanf("%s", username);
    scanf("%s", password);
    login(username, password);
    return 0;
}

void login(const char *username, const char *password) {
    if (check_login(username, password)) {
        printf("success");
    } else {
        printf("can't login");
    }
}

int check_login(const char *username, const char *password) {
    sqlite3 *db;
    sqlite3_stmt *res;

    int rc = sqlite3_open("user.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char *sql = "SELECT * FROM users WHERE username=? AND password=?";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
    rc = sqlite3_bind_text(res, 2, password, -1, SQLITE_STATIC);

    rc = sqlite3_step(res);

    if (rc == SQLITE_ROW) {
        printf("%s\n", sqlite3_column_text(res, 0));
    } else {
        fprintf(stderr, "Failed to select data\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
}