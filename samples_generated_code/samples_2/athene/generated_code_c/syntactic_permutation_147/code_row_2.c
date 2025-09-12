#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql_stmt = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?);";

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", err_msg);
    } else {
        printf("Order placed successfully!\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char stock_name[50];
    int quantity;

    printf("Enter the stock name: ");
    scanf("%49s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    handle_buy_order(stock_name, quantity);

    printf("Redirecting to stock_view page...\n");

    return 0;
}