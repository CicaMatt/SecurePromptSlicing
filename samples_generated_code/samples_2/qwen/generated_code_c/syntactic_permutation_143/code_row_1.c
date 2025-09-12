#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void unsubscribe_user(const char *email) {
    sqlite3 *db;
    char *err_message = 0;

    if (sqlite3_open(DATABASE, &db)) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE email='%s';", email);

    int rc = sqlite3_exec(db, query, callback, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return;
    }

    if (sqlite3_changes(db)) {
        snprintf(query, sizeof(query), "DELETE FROM users WHERE email='%s';", email);
        rc = sqlite3_exec(db, query, callback, 0, &err_message);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to delete user: %s\n", err_message);
            sqlite3_free(err_message);
        } else {
            printf("User unsubscribed successfully.\n");
        }
    } else {
        printf("The user is not subscribed.\n");
    }

    sqlite3_close(db);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    unsubscribe_user(argv[1]);

    return 0;
}