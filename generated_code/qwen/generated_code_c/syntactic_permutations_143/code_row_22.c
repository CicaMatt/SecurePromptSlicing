#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "mailing_list.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void unsubscribe_email(const char *email) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql_select = sqlite3_mprintf("SELECT 1 FROM subscribers WHERE email='%q';", email);
    rc = sqlite3_exec(db, sql_select, callback, 0, &zErrMsg);

    if (rc == SQLITE_ROW) {
        char *sql_delete = sqlite3_mprintf("DELETE FROM subscribers WHERE email='%q';", email);
        rc = sqlite3_exec(db, sql_delete, callback, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            printf("Unsubscribed successfully.\n");
        }
        sqlite3_free(sql_delete);
    } else {
        printf("Email is not subscribed.\n");
    }

    sqlite3_free(sql_select);
    sqlite3_close(db);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    unsubscribe_email(argv[1]);

    return 0;
}