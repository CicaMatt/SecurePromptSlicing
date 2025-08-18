#include <stdio.h>
#include <sqlite3.h>

void handle_buy_order(char *stock_symbol, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql = "INSERT INTO Orders (stock_symbol, quantity) VALUES (?, ?);";

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, stock_symbol, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, quantity);
        
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Failed to insert data: %s\n", err_msg);
        } else {
            printf("Data inserted successfully.\n");
        }
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char stock_symbol[10];
    int quantity;

    printf("Enter stock symbol: ");
    scanf("%9s", stock_symbol);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    handle_buy_order(stock_symbol, quantity);

    // Redirect to stock_view page
    printf("Redirecting to stock_view page...\n");

    return 0;
}