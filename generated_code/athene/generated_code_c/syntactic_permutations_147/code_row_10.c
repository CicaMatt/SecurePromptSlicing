#include <stdio.h>
#include <sqlite3.h>

void buy_order(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Records created successfully\n");
    }

    sqlite3_close(db);
}

void redirect_to_stock_view() {
    printf("Location: /stock_view\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Redirecting to stock view...</body></html>");
}

int main() {
    const char *stock_name = "AAPL";
    int quantity = 10;

    buy_order(stock_name, quantity);
    redirect_to_stock_view();

    return 0;
}