#include <stdio.h>
#include <sqlite3.h>

void handle_buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql;

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?);";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, quantity);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to insert data: %s\n", err_msg);
        }
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void buy_order() {
    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    handle_buy_order(stock_name, quantity);

    printf("Redirecting to stock_view...\n");
}

int main() {
    buy_order();
    return 0;
}