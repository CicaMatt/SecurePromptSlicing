#include <stdio.h>
#include <sqlite3.h>

int username_exists(sqlite3 *db, const char *username) {
    int result = 0;
    int rc;
    sqlite3_stmt *stmt;

    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        result = (sqlite3_column_int(stmt, 0) > 0);
    }

    sqlite3_finalize(stmt);
    return result;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *username = "example_user";
    if (username_exists(db, username)) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    sqlite3_close(db);
    return 0;
}