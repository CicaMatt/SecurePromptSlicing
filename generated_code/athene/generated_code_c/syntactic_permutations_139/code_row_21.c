#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char *argv[]) {
    const char *db_name = getenv("DB_NAME");
    const char *db_user = getenv("DB_USER");
    const char *db_pass = getenv("DB_PASS");
    sqlite3 *db;
    int rc;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        return 1;
    }

    rc = sqlite3_open(db_name, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT COUNT(*) FROM users WHERE username = ? AND is_moderator = 1;");
    
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, argv[1], -1, SQLITE_TRANSIENT);

    int is_mod = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_mod = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return !is_mod; // Return 0 (true in shell) if user is a moderator, 1 otherwise
}