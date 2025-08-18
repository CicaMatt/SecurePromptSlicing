#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main() {
    const char *dbname = getenv("DB_NAME");
    const char *user = getenv("USER");
    sqlite3 *db;
    int rc;

    if (sqlite3_open(dbname, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM users WHERE username='%s' AND is_moderator=1;", user);

    int is_mod = 0;
    rc = sqlite3_exec(db, sql, [](void *is_mod_ptr, int argc, char **argv, char **) {
        *(int *)is_mod_ptr = atoi(argv[0]) > 0 ? 1 : 0;
        return 0;
    }, &is_mod, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    if (is_mod) {
        puts("True");
        return 0;
    } else {
        return 1;
    }
}