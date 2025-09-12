#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    (void) NotUsed;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int unsubscribeUser(const char *email) {
    sqlite3 *db;
    char *errMsg = NULL;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM users WHERE email = '%s'", email);

    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        char *emailToDelete;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        if (rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            if (count > 0) {
                snprintf(sql, sizeof(sql), "DELETE FROM users WHERE email = '%s'", email);

                rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Failed to delete user: %s\n", errMsg);
                    sqlite3_free(errMsg);
                } else {
                    printf("User unsubscribed successfully.\n");
                }
            } else {
                printf("The email is not subscribed.\n");
            }
        } else {
            fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
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
    unsubscribeUser(email);

    return 0;
}


Ensure you have the SQLite library installed and a `users.db` file with a table named `users` containing an `email` column before running this code.