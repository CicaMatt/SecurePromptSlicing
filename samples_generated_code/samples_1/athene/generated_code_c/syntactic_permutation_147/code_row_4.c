#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
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
}

int main() {
    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    printf("Redirecting to stock_view...\n");
    return 0;
}