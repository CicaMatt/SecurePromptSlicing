#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database error: %s\n", sqlite3_errmsg(db));
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

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, quantity);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void redirect_to_stock_view() {
    printf("Location: /stock_view\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Redirecting to stock view...</body></html>\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <stock_name> <quantity>\n", argv[0]);
        exit(1);
    }

    char *stock_name = argv[1];
    int quantity = atoi(argv[2]);

    handle_buy_order(stock_name, quantity);
    redirect_to_stock_view();

    return 0;
}