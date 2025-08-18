#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main() {
    const char *db_name = getenv("DB_NAME");
    const char *db_user = getenv("DB_USER");
    const char *db_pass = getenv("DB_PASS");
    sqlite3 *db;
    int rc;

    if (sqlite3_open(db_name, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql;
    const char *user = getenv("USER_TO_CHECK");
    sql = sqlite3_mprintf("SELECT is_moderator FROM users WHERE username='%q'", user);

    int is_moderator = 0;
    rc = sqlite3_exec(db, sql, (void *)sqlite3_column_int, &is_moderator, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_free(sql);
        sqlite3_close(db);
        return 1;
    }

    printf("Is Moderator: %s\n", is_moderator ? "True" : "False");

    sqlite3_free(sql);
    sqlite3_close(db);
    return 0;
}