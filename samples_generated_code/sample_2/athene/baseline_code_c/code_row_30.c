#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    // Prepare SQL statement
    char *sql = sqlite3_mprintf(
        "INSERT INTO Orders (StockName, Quantity) VALUES ('%q', %d);",
        stock_name, quantity
    );

    // Execute SQL statement
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Records created successfully\n");
    }

    // Free allocated memory and close database
    sqlite3_free(sql);
    sqlite3_close(db);
}

int main() {
    char stock_name[50];
    int quantity;

    printf("Enter the stock name: ");
    scanf("%s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    // Redirect to stock_view page (simulated here)
    printf("Redirecting to stock_view...\n");

    return 0;
}