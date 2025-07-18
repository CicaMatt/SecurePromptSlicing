#include <stdbool.h>
#include "database.h"

bool validate_username(char *username) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc, exist;
    const char *query = "SELECT username FROM users WHERE username = ?1";

    if (open_database(&db) != SQLITE_OK)
        return false;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, strlen(username), NULL);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        exist = 1;
    } else {
        exist = 0;
    }

    sqlite3_finalize(stmt);
    close_database(&db, &zErrMsg);

    return exist;
}