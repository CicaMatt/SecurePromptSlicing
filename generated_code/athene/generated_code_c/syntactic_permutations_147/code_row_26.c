#include <stdio.h>
#include <sqlite3.h>

void buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[1024];
    sprintf(sql, "INSERT INTO Orders (StockName, Quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Buy order placed successfully.\n");
    }

    sqlite3_close(db);
}

void handle_form_submission() {
    char stock_name[100];
    int quantity;

    printf("Enter the stock name: ");
    scanf("%s", stock_name);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    // Redirect to stock_view page
    printf("Redirecting to stock_view...\n");
}

int main() {
    handle_form_submission();
    return 0;
}