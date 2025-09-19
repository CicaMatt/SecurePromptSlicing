#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int check_and_unsubscribe(const char *email) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM users WHERE email = '%q';", email);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        if (sqlite3_changes(db) == 0) {
            printf("User is not subscribed.\n");
        } else {
            fprintf(stderr, "SQL error: %s\n", err_message);
            sqlite3_free(err_message);
        }
    } else {
        printf("User unsubscribed successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    check_and_unsubscribe(email);

    return 0;
}