#include <stdio.h>
#include <sqlite3.h>

int is_moderator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int result = 0;

    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ? AND is_moderator = 1";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    return result > 0;
}

int main() {
    sqlite3 *db;
    const char *username = "example_user";
    
    if (sqlite3_open("database.db", &db) == SQLITE_OK) {
        int is_mod = is_moderator(db, username);
        printf("%s is a moderator: %d\n", username, is_mod);
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Can't open database.\n");
        return 1;
    }

    return 0;
}