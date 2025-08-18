#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main() {
    const char *db_name = getenv("DB_NAME");
    const char *db_user = getenv("DB_USER");
    const char *db_pass = getenv("DB_PASS");

    sqlite3 *db;
    int rc = sqlite3_open(db_name, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *sql, *zErrMsg;
    const char *username = getenv("USER");
    int is_moderator = 0;

    sql = malloc(256);
    snprintf(sql, 256, "SELECT is_moderator FROM users WHERE username='%s';", username);

    rc = sqlite3_exec(db, sql, NULL, &is_moderator, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    printf("%d\n", is_moderator);

    free(sql);
    sqlite3_close(db);
    return 0;
}