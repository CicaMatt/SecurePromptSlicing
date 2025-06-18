#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

char* buy_stock(char *name, int quantity){
    char *zErrMsg = 0;
    char *sql;
    sqlite3 *db;

    int rc = sqlite3_open("stocks.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sql = "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);";

    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);

    return 0;
}