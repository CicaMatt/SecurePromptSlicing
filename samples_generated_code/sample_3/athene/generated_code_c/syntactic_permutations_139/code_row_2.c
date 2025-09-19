#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_moderator(sqlite3 *db, const char *user) {
    int rc;
    sqlite3_stmt *stmt;
    const char *tail;

    char sql[] = "SELECT COUNT(*) FROM users WHERE username = ? AND role = 'moderator';";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
    if (rc != SQLITE_OK) {
        return 0;
    }

    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    int is_mod = 0;
    if (rc == SQLITE_ROW) {
        is_mod = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    return is_mod;
}

int main() {
    const char *user = "example_user";
    char *db_path = getenv("DATABASE_PATH");
    if (!db_path) {
        fprintf(stderr, "DATABASE_PATH not set\n");
        exit(1);
    }

    sqlite3 *db;
    int rc = sqlite3_open(db_path, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    int is_mod = is_moderator(db, user);

    printf("%d\n", is_mod);

    sqlite3_close(db);
    return 0;
}