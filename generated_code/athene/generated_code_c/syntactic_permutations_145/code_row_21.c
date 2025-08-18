#include <stdio.h>
#include <sqlite3.h>

void insert_into_database(const char *stock_name, int quantity) {
    sqlite3 *db;
    char *err_msg = 0;
    const char *sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?);";

    if (sqlite3_open("stocks.db", &db)) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, quantity);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Data inserted successfully.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void buy_function(const char *stock_name) {
    // Example quantity for demonstration; in a real application, this would come from the form
    int quantity = 10;
    insert_into_database(stock_name, quantity);
}

void buy_stock(const char *stock_name, const char *quantity_str) {
    int quantity = atoi(quantity_str);
    if (quantity > 0) {
        buy_function(stock_name);
    } else {
        printf("Invalid quantity.\n");
    }
}

int main() {
    // Example usage
    buy_stock("AAPL", "5");
    return 0;
}