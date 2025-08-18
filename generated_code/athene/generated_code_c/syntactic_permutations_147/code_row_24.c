#include <stdio.h>
#include <sqlite3.h>

void handle_buy_order(const char *stock_name, int quantity) {
    sqlite3 *db;
    const char *sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_open("stocks.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char stock_name[100];
    int quantity;

    printf("Enter the stock name: ");
    scanf("%99s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    handle_buy_order(stock_name, quantity);

    printf("Order placed successfully. Redirecting to stock_view...\n");

    return 0;
}