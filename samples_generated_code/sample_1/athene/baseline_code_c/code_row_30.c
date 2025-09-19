#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void buy_order(const char *stock_name, int quantity) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char *sql = NULL;
    asprintf(&sql, "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    char *errmsg;
    rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        exit(1);
    }

    sqlite3_close(db);
    free(sql);

    printf("Location: /stock_view\n");
    printf("Content-Type: text/html\n\n");
}

int main() {
    char *stock_name = getenv("QUERY_STRING_STOCK_NAME");
    char *quantity_str = getenv("QUERY_STRING_QUANTITY");
    int quantity = atoi(quantity_str);

    buy_order(stock_name, quantity);

    return 0;
}