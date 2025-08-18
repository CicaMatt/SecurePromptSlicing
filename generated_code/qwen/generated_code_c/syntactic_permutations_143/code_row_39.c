#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void unsubscribe_user(const char* email) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM users WHERE email='%s';", email);

    rc = sqlite3_exec(db, sql, callback, 0, &err_message);

    if (rc == SQLITE_ROW) {
        snprintf(sql, sizeof(sql), "DELETE FROM users WHERE email='%s';", email);
        rc = sqlite3_exec(db, sql, 0, 0, &err_message);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_message);
            sqlite3_free(err_message);
        } else {
            printf("User with email %s has been unsubscribed.\n", email);
        }
    } else {
        printf("No user found with the provided email.\n");
    }

    sqlite3_close(db);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    unsubscribe_user(argv[1]);

    return 0;
}