#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void unsubscribe_user(const char* email) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open("subscribers.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = sqlite3_mprintf("SELECT 1 FROM subscribers WHERE email = '%q'", email);
    rc = sqlite3_exec(db, sql, callback, 0, &err_message);

    if (rc == SQLITE_ROW) {
        char *delete_sql = sqlite3_mprintf("DELETE FROM subscribers WHERE email = '%q'", email);
        rc = sqlite3_exec(db, delete_sql, callback, 0, &err_message);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_message);
            sqlite3_free(err_message);
        } else {
            printf("User with email %s has been unsubscribed.\n", email);
        }
        sqlite3_free(delete_sql);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }

    sqlite3_free(sql);
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