#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "orders.db"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void create_table() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS orders(" \
                      "id INTEGER PRIMARY KEY AUTOINCREMENT," \
                      "quantity INT NOT NULL," \
                      "price REAL NOT NULL);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
}

void insert_order(int quantity, double price) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO orders(quantity, price) VALUES (%d, %.2f);", quantity, price);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
}

int main() {
    create_table();

    int quantity;
    double price;

    printf("Enter the quantity of stocks to buy: ");
    scanf("%d", &quantity);

    printf("Enter the price per stock: ");
    scanf("%lf", &price);

    insert_order(quantity, price);

    printf("Order submitted successfully. Redirecting to stock_view page...\n");

    return 0;
}