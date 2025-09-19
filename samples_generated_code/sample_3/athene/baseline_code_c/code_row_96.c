#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void insert_buy_order(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d);", username, stock_name, stock_quantity);
    sqlite3_exec(db, sql, callback, 0, NULL);
}

int main() {
    const char *username = "user123";
    const char *stock_name = "AAPL";
    int stock_quantity = 50;

    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    insert_buy_order(db, username, stock_name, stock_quantity);

    sqlite3_close(db);
    printf("Location: /profile.html\n\n");
    return 0;
}