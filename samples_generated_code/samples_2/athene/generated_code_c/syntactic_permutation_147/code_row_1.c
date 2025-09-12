#include <stdio.h>
#include <sqlite3.h>

void handle_buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?);";

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void buy_order(char *stock_name, int quantity) {
    handle_buy_order(stock_name, quantity);
    printf("Location: /stock_view\r\n");
    printf("\r\n");
}

int main() {
    char stock_name[50];
    int quantity;

    printf("Content-Type: text/html\r\n\r\n");

    printf("<form method='post' action='/buy_order'>\n");
    printf("Stock Name: <input type='text' name='stock_name'><br>\n");
    printf("Quantity: <input type='number' name='quantity'><br>\n");
    printf("<input type='submit' value='Submit'>\n");
    printf("</form>");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        sscanf(getenv("QUERY_STRING"), "stock_name=%s&quantity=%d", stock_name, &quantity);
        buy_order(stock_name, quantity);
    }

    return 0;
}