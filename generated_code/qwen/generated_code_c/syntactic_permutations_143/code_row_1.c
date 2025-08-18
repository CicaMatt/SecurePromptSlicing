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
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), "SELECT * FROM users WHERE email='%s';", email);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc == SQLITE_ROW) {
        snprintf(sql, sizeof(sql), "DELETE FROM users WHERE email='%s';", email);
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            printf("User with email %s has been unsubscribed.\n", email);
        }
    } else {
        printf("User with email %s is not subscribed.\n", email);
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