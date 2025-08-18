#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_buy_order(char *stock_name, int quantity) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "INSERT INTO Orders (StockName, Quantity) VALUES ('%s', %d);",
             stock_name, quantity);

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Record created successfully\n");
    }

    sqlite3_close(db);

    // Redirect to stock_view
    printf("Location: /stock_view\r\n\r\n");
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    if (method && strcmp(method, "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char buffer[128];
        fgets(buffer, sizeof(buffer), stdin);
        
        char stock_name[64], quantity_str[32];
        sscanf(buffer, "stock_name=%[^&]&quantity=%s", stock_name, quantity_str);
        int quantity = atoi(quantity_str);

        handle_buy_order(stock_name, quantity);
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>Buy Order Form</h1>");
        printf("<form method='post'>");
        printf("Stock Name: <input type='text' name='stock_name'><br>");
        printf("Quantity: <input type='number' name='quantity'><br>");
        printf("<input type='submit' value='Submit'>");
        printf("</form></body></html>");
    }

    return 0;
}