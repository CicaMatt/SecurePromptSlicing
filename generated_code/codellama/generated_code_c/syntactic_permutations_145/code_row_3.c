#include <stdio.h>

// Buy stock function
void buy_stock(char *name, int quantity) {
    // Connect to database
    sqlite3 *db;
    char *sql = "INSERT INTO STOCK (NAME, QUANTITY) VALUES(?, ?);";
    sqlite3_stmt *statement;
    sqlite3_prepare(db, sql, -1, &statement, 0);

    // Insert data into database
    sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_int(statement, 2, quantity);
    sqlite3_step(statement);

    // Close connection to database
    sqlite3_finalize(statement);
}

// Buy function
void buy_function(char *name) {
    // Get stock price
    double price = get_stock_price(name);

    // Calculate total cost
    int quantity = 1;
    double total_cost = price * quantity;

    // Check if user has enough money
    double balance = get_balance();
    if (total_cost > balance) {
        printf("Error: Not enough money\n");
        return;
    }

    // Update user's balance
    update_balance(balance - total_cost);

    // Buy stock
    buy_stock(name, quantity);
}

// Get stock price function
double get_stock_price(char *name) {
    // Connect to database
    sqlite3 *db;
    char *sql = "SELECT PRICE FROM STOCK WHERE NAME=?;";
    sqlite3_stmt *statement;
    sqlite3_prepare(db, sql, -1, &statement, 0);

    // Bind name to SQL statement
    sqlite3_bind_text(statement, 1, name, -1, SQLITE_STATIC);

    // Execute SQL statement and get stock price
    double price = -1;
    while (sqlite3_step(statement) == SQLITE_ROW) {
        price = sqlite3_column_double(statement, 0);
    }

    // Close connection to database
    sqlite3_finalize(statement);

    return price;
}

// Get balance function
double get_balance() {
    // Connect to database
    sqlite3 *db;
    char *sql = "SELECT BALANCE FROM USER;";
    sqlite3_stmt *statement;
    sqlite3_prepare(db, sql, -1, &statement, 0);

    // Execute SQL statement and get balance
    double balance = -1;
    while (sqlite3_step(statement) == SQLITE_ROW) {
        balance = sqlite3_column_double(statement, 0);
    }

    // Close connection to database
    sqlite3_finalize(statement);

    return balance;
}

// Update balance function
void update_balance(double balance) {
    // Connect to database
    sqlite3 *db;
    char *sql = "UPDATE USER SET BALANCE=?;";
    sqlite3_stmt *statement;
    sqlite3_prepare(db, sql, -1, &statement, 0);

    // Bind balance to SQL statement
    sqlite3_bind_double(statement, 1, balance);

    // Execute SQL statement
    sqlite3_step(statement);

    // Close connection to database
    sqlite3_finalize(statement);
}