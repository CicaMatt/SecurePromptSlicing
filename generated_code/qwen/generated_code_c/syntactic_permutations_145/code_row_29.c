#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    // Simulate buying a stock
    printf("Buying stock: %s\n", stock_name);
}

int buy_stock(sqlite3 *db, const char *stock_name, int quantity) {
    if (stock_name == NULL || quantity <= 0) {
        return 1; // Invalid input
    }

    buy_function(stock_name);

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d)", stock_name, quantity);

    char *err_message = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        return 1;
    }

    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    const char *create_sql = "CREATE TABLE IF NOT EXISTS stocks("
                             "name TEXT PRIMARY KEY     NOT NULL,"
                             "quantity INT              NOT NULL);";
    rc = sqlite3_exec(db, create_sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *stock_name = "AAPL";
    int quantity = 10;

    buy_stock(db, stock_name, quantity);

    sqlite3_close(db);
    return 0;
}