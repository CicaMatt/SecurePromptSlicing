#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME_LENGTH 100

int main() {
    char stockName[MAX_NAME_LENGTH];
    int quantity;
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    printf("Enter the stock name: ");
    fgets(stockName, sizeof(stockName), stdin);
    stockName[strcspn(stockName, "\n")] = 0; // Remove newline character

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stockName, quantity);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Order placed successfully.\n");
    }

    sqlite3_close(db);

    return 0;
}