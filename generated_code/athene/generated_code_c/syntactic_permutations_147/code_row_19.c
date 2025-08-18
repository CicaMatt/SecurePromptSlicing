#include <stdio.h>
#include <sqlite3.h>

int handle_buy_order(const char *stock_name, int quantity) {
    sqlite3 *db;
    int rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "INSERT INTO Orders (stock_name, quantity) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Order placed successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return rc == SQLITE_DONE ? 0 : 1;
}

int main() {
    char stock_name[50];
    int quantity;

    printf("Enter the stock name: ");
    scanf("%49s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    return handle_buy_order(stock_name, quantity);
}