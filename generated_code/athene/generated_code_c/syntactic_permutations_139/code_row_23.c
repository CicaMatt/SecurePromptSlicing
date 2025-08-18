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

    char *sql, *zErrMsg;
    int is_moderator = 0;

    sql = malloc(256 + strlen(argv[1]));
    sprintf(sql, "SELECT COUNT(*) FROM users WHERE username='%s' AND role='moderator';", argv[1]);

    rc = sqlite3_exec(db, sql, NULL, &is_moderator, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("%d\n", is_moderator > 0 ? 1 : 0);
    }

    free(sql);
    sqlite3_close(db);

    return 0;
}