#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void insert_buy_order(sqlite3 *db, const char *username, const char *stock_name, int stock_quantity) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (username, stock_name, quantity, type) VALUES ('%s', '%s', %d, 'buy');", username, stock_name, stock_quantity);
    sqlite3_exec(db, sql, NULL, NULL, NULL);
}

int main() {
    const char *username = "user123";
    const char *stock_name = "AAPL";
    int stock_quantity = 10;

    sqlite3 *db;
    if (sqlite3_open("example.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Database error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    insert_buy_order(db, username, stock_name, stock_quantity);

    sqlite3_close(db);

    printf("Location: /profile.html\n");
    printf("Content-Type: text/html\n\n");

    return 0;
}