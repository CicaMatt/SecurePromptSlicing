#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Open the database (or create it if it doesn't exist)
    rc = sqlite3_open("stocks.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    // Create table if not exists
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS orders (" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "stock_name TEXT NOT NULL," \
        "quantity INTEGER NOT NULL);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return(1);
    }

    // Example stock name and quantity from user input
    char stock_name[] = "AAPL";
    int quantity = 10;

    // Prepare SQL statement for inserting data
    const char *sql_insert =
        "INSERT INTO orders (stock_name, quantity) VALUES (?, ?);";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, stock_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, quantity);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
    }

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}