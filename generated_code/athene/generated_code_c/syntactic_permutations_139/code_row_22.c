#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main() {
    const char *db_name = getenv("DATABASE_NAME");
    const char *db_user = getenv("DATABASE_USER");
    const char *db_pass = getenv("DATABASE_PASS");
    const char *username = "example_username"; // Replace with the username to check

    sqlite3 *db;
    int rc = sqlite3_open(db_name, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT COUNT(*) FROM users WHERE username='%s' AND is_admin=1;", username);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int isAdmin = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        isAdmin = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (isAdmin) {
        return 0; // True
    } else {
        return 1; // False
    }
}