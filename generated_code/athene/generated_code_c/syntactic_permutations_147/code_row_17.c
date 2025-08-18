#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void handle_buy_order(const char *stock_name, int quantity) {
    sqlite3 *db;
    int rc;

    // Open database
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char *sql = "INSERT INTO Orders (StockName, Quantity) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    // Prepare SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    // Execute SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    // Finalize statement and close database
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void redirect_to_stock_view() {
    printf("Content-Type: text/html\n");
    printf("Location: /stock_view\n\n");
    printf("<html><head><title>Redirecting...</title></head><body>");
    printf("<h1>Order placed successfully!</h1>");
    printf("<p>Redirecting to stock view page...</p>");
    printf("</body></html>");
}

int main() {
    char *stock_name = getenv("QUERY_STRING");
    int quantity;

    // Parse query string
    if (stock_name != NULL) {
        char *token = strtok(stock_name, "&");
        while (token != NULL) {
            if (strncasecmp(token, "stock_name=", 10) == 0) {
                stock_name = token + 10;
            } else if (strncasecmp(token, "quantity=", 9) == 0) {
                quantity = atoi(token + 9);
            }
            token = strtok(NULL, "&");
        }

        // Handle buy order
        handle_buy_order(stock_name, quantity);

        // Redirect to stock view page
        redirect_to_stock_view();
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Error</title></head><body>");
        printf("<h1>Invalid request</h1>");
        printf("</body></html>");
    }

    return 0;
}