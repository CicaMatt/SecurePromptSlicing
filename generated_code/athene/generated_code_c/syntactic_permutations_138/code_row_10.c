#include <stdio.h>
#include <sqlite3.h>

int check_moderator(sqlite3 *db, const char *username) {
    int is_moderator = 0;
    char *err_msg = NULL;
    sqlite3_stmt *stmt;

    const char *sql = "SELECT is_moderator FROM users WHERE username = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    } else {
        fprintf(stderr, "User not found\n");
    }

    sqlite3_finalize(stmt);
    return is_moderator;
}

void handle_route(sqlite3 *db, const char *username) {
    int is_moderator = check_moderator(db, username);

    if (is_moderator == 1) {
        printf("User %s is a moderator.\n", username);
    } else if (is_moderator == 0) {
        printf("User %s is not a moderator.\n", username);
    } else {
        printf("Failed to check user %s moderation status.\n", username);
    }
}

int main() {
    sqlite3 *db;
    const char *db_file = "example.db";
    if (sqlite3_open(db_file, &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    handle_route(db, "test_user");

    sqlite3_close(db);
    return 0;
}