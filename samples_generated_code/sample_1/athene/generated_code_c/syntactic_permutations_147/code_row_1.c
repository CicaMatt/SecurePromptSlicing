#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_form_submission(char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    char *sql = "INSERT INTO Orders (StockName, Quantity) VALUES (?, ?);";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", err_msg);
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", err_msg);
    } else {
        printf("Data inserted successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void buy_order(char *stock_name, int quantity) {
    handle_form_submission(stock_name, quantity);
    printf("Location: /stock_view\n");
    printf("Content-Type: text/html\n\n");
    printf("<html><body>Order placed successfully. Redirecting to stock view...</body></html>");
}

int main() {
    char stock_name[100];
    int quantity;

    printf("Content-Type: text/html\n\n");
    printf("<form method='post' action='/buy_order'>");
    printf("Stock Name: <input type='text' name='stock_name'><br>");
    printf("Quantity: <input type='number' name='quantity'><br>");
    printf("<input type='submit' value='Submit'></form>");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char *buffer = malloc(content_length + 1);
        fread(buffer, 1, content_length, stdin);
        buffer[content_length] = '\0';

        sscanf(buffer, "stock_name=%[^&]&quantity=%d", stock_name, &quantity);

        buy_order(stock_name, quantity);
    }

    return 0;
}