#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }

    char sql[256];
    sprintf(sql, "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Data inserted successfully.\n");
    }

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
    // In a real web application, this would be handled by an HTTP redirect
    return 0;
}