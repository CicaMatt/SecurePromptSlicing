#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME_LENGTH 256

void buy_order(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    }

    sqlite3_close(db);
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int quantity;

    printf("Enter stock name: ");
    scanf("%255s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    printf("Redirecting to stock_view page...\n");
    return 0;
}