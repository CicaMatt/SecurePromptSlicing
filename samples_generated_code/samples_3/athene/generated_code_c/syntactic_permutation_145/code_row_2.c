#include <stdio.h>
#include <sqlite3.h>

void buy_function(int quantity) {
    sqlite3 *db;
    int rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[100];
    sprintf(sql, "INSERT INTO transactions (quantity) VALUES (%d);", quantity);

    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);
}

void buy_stock(int quantity) {
    buy_function(quantity);
}