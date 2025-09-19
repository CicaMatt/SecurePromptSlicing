#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char *argv[]) {
    const char *env_db_path = getenv("DB_PATH");
    const char *env_user_id = getenv("USER_ID");

    if (!env_db_path || !env_user_id) {
        fprintf(stderr, "Environment variables DB_PATH and USER_ID must be set.\n");
        return 1;
    }

    sqlite3 *db;
    int rc = sqlite3_open(env_db_path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT is_moderator FROM users WHERE id = '%s'", env_user_id);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int is_moderator = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        is_moderator = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (is_moderator) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}