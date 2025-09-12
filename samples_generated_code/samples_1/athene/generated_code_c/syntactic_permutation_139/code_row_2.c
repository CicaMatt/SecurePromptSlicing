#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char *argv[]) {
    sqlite3 *db;
    const char *env_db = getenv("DATABASE_URL");
    const char *user = getenv("USER");

    if (sqlite3_open(env_db, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int is_moderator = 0;
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM users WHERE username='%s' AND role='moderator';", user);
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            is_moderator = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);

    return is_moderator ? 0 : 1;
}