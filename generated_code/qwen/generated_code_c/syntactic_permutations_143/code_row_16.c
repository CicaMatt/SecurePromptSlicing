#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "subscribers.db"
#define EMAIL_LENGTH 256

int check_and_delete_email(const char *email) {
    sqlite3 *db;
    char sql[512];
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM subscribers WHERE email='%q';", email);

    int exists = 0;
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    if (exists) {
        snprintf(sql, sizeof(sql), "DELETE FROM subscribers WHERE email='%q';", email);
        rc = sqlite3_exec(db, sql, 0, 0, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }

    sqlite3_close(db);
    return exists;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    check_and_delete_email(email);

    return 0;
}