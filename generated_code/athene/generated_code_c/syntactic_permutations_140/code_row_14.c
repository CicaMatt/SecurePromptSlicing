#include <stdio.h>
#include <sqlite3.h>

int check_exists(sqlite3 *db, const char *table, const char *column, const char *value) {
    int exists = 0;
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT CASE WHEN EXISTS (SELECT 1 FROM %s WHERE %s = '%s') THEN 1 ELSE 0 END;", table, column, value);
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return exists;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *table = "users";
    const char *column = "username";
    const char *value = "john_doe";

    int result = check_exists(db, table, column, value);
    
    printf("Exists: %s\n", result ? "true" : "false");

    sqlite3_close(db);
    return 0;
}