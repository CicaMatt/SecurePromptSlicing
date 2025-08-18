#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_NAME_LENGTH 50

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[100];
    char stock_name[MAX_NAME_LENGTH];
    int quantity;

    printf("Enter the stock name: ");
    scanf("%s", stock_name);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    rc = sqlite3_open("stock.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    snprintf(sql, sizeof(sql), "CREATE TABLE IF NOT EXISTS orders(stock_name TEXT, quantity INTEGER);");
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    snprintf(sql, sizeof(sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Order placed successfully!\n");
    }

    sqlite3_close(db);
    return 0;
}