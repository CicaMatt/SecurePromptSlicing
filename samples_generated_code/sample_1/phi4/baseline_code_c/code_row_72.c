#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void buy_function(const char *stock_name) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM stocks WHERE name='%s';", stock_name);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Operation done successfully\n");
    }

    sqlite3_close(db);
}

void buy_stock(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char sql[512];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO stocks (name, quantity) VALUES ('%s', '%d');", stock_name, quantity);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Stock purchased successfully\n");
    }

    buy_function(stock_name);

    sqlite3_close(db);
}

int main() {
    // Example usage
    char stock_name[] = "AAPL";
    int quantity = 10;

    buy_stock(stock_name, quantity);

    return 0;
}


To make this code runnable:
1. Install SQLite development libraries.
2. Create a database `stocks.db` with a table `stocks` having columns `name` (TEXT) and `quantity` (INTEGER).