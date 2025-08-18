#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql;

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    sql = "CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)";
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    char insert_sql[256];
    snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d)", stock_name, quantity);

    if (sqlite3_exec(db, insert_sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><head><title>Stock View</title></head><body>");
    printf("<h1>Order Placed Successfully!</h1>");
    printf("<p>Your order for %d shares of %s has been placed.</p>", quantity, stock_name);
    printf("</body></html>");

    sqlite3_close(db);
}

int main() {
    char *stock_name = getenv("STOCK_NAME");
    char *quantity_str = getenv("QUANTITY");

    if (stock_name == NULL || quantity_str == NULL) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><head><title>Error</title></head><body>");
        printf("<h1>Missing required parameters.</h1>");
        printf("</body></html>");
        return 1;
    }

    int quantity = atoi(quantity_str);
    handle_buy_order(stock_name, quantity);

    return 0;
}