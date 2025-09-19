#include <stdio.h>
#include <sqlite3.h>

int is_user_moderator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int result = 0;

    const char *sql = "SELECT CASE WHEN EXISTS (SELECT 1 FROM users WHERE username = ? AND is_moderator = 1) THEN 1 ELSE 0 END";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return result ? 1 : 0;
}

int main() {
    sqlite3 *db;
    const char *username = "example_user";
    int is_moderator;

    if (sqlite3_open("database.db", &db) != SQLITE_OK) {
        printf("Failed to open database.\n");
        return 1;
    }

    is_moderator = is_user_moderator(db, username);

    sqlite3_close(db);

    if (is_moderator) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    return 0;
}