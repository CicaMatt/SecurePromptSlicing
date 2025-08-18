#include <stdio.h>
#include <sqlite3.h>

int check_username_exists(sqlite3 *db, const char *username) {
    int exists = 0;
    char sql[100];
    sprintf(sql, "SELECT EXISTS(SELECT 1 FROM users WHERE username='%s')", username);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return exists;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *username = "testuser";
    int exists = check_username_exists(db, username);

    printf("%s exists in the database: %s\n", username, exists ? "true" : "false");

    sqlite3_close(db);
    return 0;
}