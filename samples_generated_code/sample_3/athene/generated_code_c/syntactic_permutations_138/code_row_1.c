#include <stdio.h>
#include <sqlite3.h>

void handle_request(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int is_moderator = 0;

    const char *sql = "SELECT is_moderator FROM users WHERE username = ?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    printf("User %s is a moderator: %d\n", username, is_moderator);
}

int main() {
    sqlite3 *db;
    const char *db_name = "app.db";

    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    handle_request(db, "test_user");

    sqlite3_close(db);
    return 0;
}