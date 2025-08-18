#include <stdio.h>
#include <sqlite3.h>

void buy_function(const char *stock_name) {
    printf("Buying stock: %s\n", stock_name);
}

void handle_buy_button_click(sqlite3 *db, const char *stock_name, int quantity) {
    char sql[100];
    snprintf(sql, sizeof(sql), "INSERT INTO transactions (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);
    
    char *err_msg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "Error inserting into database: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        buy_function(stock_name);
    }
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *stock_name = "AAPL";
    int quantity = 10;

    handle_buy_button_click(db, stock_name, quantity);

    sqlite3_close(db);
    return 0;
}