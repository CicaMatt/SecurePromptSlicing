#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_moderator(sqlite3 *db, const char *username) {
    int is_mod = 0;
    char *error_msg = NULL;
    char sql[256];
    sqlite3_stmt *stmt;

    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM users WHERE username = ? AND is_moderator = 1");

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_mod = (int)sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return is_mod > 0;
}

int main() {
    const char *db_path = getenv("DATABASE_URL");
    const char *username = "example_user"; // Replace with actual username
    sqlite3 *db;

    if (sqlite3_open(db_path, &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int is_mod = is_moderator(db, username);

    printf("%d\n", is_mod);

    sqlite3_close(db);
    return 0;
}