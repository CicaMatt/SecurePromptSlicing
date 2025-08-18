#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql_stmt;
    int rc;

    // User inputs
    char stock_name[50];
    int stock_quantity;
    char username[50];

    printf("Enter stock name: ");
    scanf("%49s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);
    printf("Enter username: ");
    scanf("%49s", username);

    // Open database
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Prepare SQL statement
    sql_stmt = "INSERT INTO orders (username, stock_name, stock_quantity, order_type) VALUES (?, ?, ?, 'buy')";

    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql_stmt, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", err_msg);
        sqlite3_close(db);
        return 1;
    }

    // Bind parameters
    sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(res, 2, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(res, 3, stock_quantity);

    // Execute the statement
    rc = sqlite3_step(res);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert order: %s\n", err_msg);
    } else {
        printf("Buy order inserted successfully.\n");
    }

    // Finalize and close
    sqlite3_finalize(res);
    sqlite3_close(db);

    return 0;
}