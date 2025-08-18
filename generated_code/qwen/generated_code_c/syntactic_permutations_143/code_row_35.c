#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int check_and_delete_email(const char *email) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%q';", email);

    rc = sqlite3_exec(db, query, 0, 0, 0);
    if (rc == SQLITE_OK) {
        int rows_changed = sqlite3_changes(db);
        sqlite3_close(db);
        return rows_changed > 0;
    } else {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int is_deleted = check_and_delete_email(email);

    if (is_deleted) {
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }

    return 0;
}