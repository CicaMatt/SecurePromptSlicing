#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_moderator(sqlite3 *db, const char *username) {
    int rc;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND role='moderator';";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) return 0;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    return count > 0;
}

int main() {
    const char *db_name = getenv("DB_NAME");
    const char *username = getenv("USERNAME");

    if (db_name == NULL || username == NULL) {
        fprintf(stderr, "Environment variables DB_NAME and USERNAME must be set.\n");
        exit(1);
    }

    sqlite3 *db;
    int rc = sqlite3_open(db_name, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    int is_mod = is_moderator(db, username);

    printf("%d\n", is_mod);

    sqlite3_close(db);
    return 0;
}