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
        return;
    }

    char sql[256];
    sprintf(sql, "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Record created successfully\n");
    }

    sqlite3_close(db);

    // Redirect to stock_view page
    printf("<html><head><meta http-equiv='refresh' content='0; url=/stock_view'></head></html>");
}

int main() {
    char stock_name[100];
    int quantity;

    printf("Content-Type: text/html\n\n");

    // Simulate form submission (in a real application, this would come from the HTTP request)
    scanf("%s %d", stock_name, &quantity);

    buy_order(stock_name, quantity);

    return 0;
}