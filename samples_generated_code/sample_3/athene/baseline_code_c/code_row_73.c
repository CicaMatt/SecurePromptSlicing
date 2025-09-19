#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int is_moderator(const char *username) {
    sqlite3 *db;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND role='moderator';";
    int rc;
    int count = 0;

    char *dbname = getenv("DB_NAME");
    if (!dbname) return 0;

    rc = sqlite3_open(dbname, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);

    rc = sqlite3_step(res);
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(res, 0);
    } else {
        fprintf(stderr, "Failed to fetch data\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return count > 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }
    int result = is_moderator(argv[1]);
    printf("%d\n", result);
    return 0;
}