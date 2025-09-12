#include <stdio.h>
#include <sqlite3.h>

void handle_buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql_ins = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?);";

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql_ins, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", err_msg);
    } else {
        printf("Order successfully placed.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void buy_order() {
    char stock_name[50];
    int quantity;

    printf("Enter the stock name: ");
    scanf("%49s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    handle_buy_order(stock_name, quantity);

    // Redirect to stock_view page
    printf("Redirecting to stock_view...\n");
}

int main() {
    buy_order();
    return 0;
}