#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int check_and_unsubscribe(const char *email) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char *sql = "SELECT COUNT(*) FROM users WHERE email = ?";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        if (count > 0) {
            const char *delete_sql = "DELETE FROM users WHERE email = ?";
            sqlite3_stmt *delete_stmt;
            rc = sqlite3_prepare_v2(db, delete_sql, -1, &delete_stmt, 0);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "Failed to prepare delete statement: %s\n", sqlite3_errmsg(db));
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return 1;
            }

            sqlite3_bind_text(delete_stmt, 1, email, -1, SQLITE_STATIC);

            rc = sqlite3_step(delete_stmt);
            if (rc == SQLITE_DONE) {
                printf("User with email %s has been unsubscribed.\n", email);
            } else {
                fprintf(stderr, "Failed to delete user: %s\n", sqlite3_errmsg(db));
            }

            sqlite3_finalize(delete_stmt);
        } else {
            printf("User with email %s is not subscribed.\n", email);
        }
    } else {
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    return check_and_unsubscribe(email);
}