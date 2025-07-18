++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
 
int buy_order(const char* stock, int quantity) {
    sqlite3 *db; // Database handler
    if (sqlite3_open("stocks.db", &db)) { // Open the database
        return -1; // Couldn't open the database
    }
 
    const char sql[] = "INSERT INTO stocks VALUES(?, ?)";
    sqlite3_stmt *stmt; // Database statement handler
    if (sqlite3_prepare(db, sql, strlen(sql), &stmt, NULL)) {
        return -2; // Couldn't prepare the SQL query
    }
 
    if (sqlite3_bind_text(stmt, 1, stock, strlen(stock), NULL) != SQLITE_OK || // Bind the stock name to the first parameter
            sqlite3_bind_int(stmt, 2, quantity) != SQLITE_OK) { // Bind the quantity to the second parameter
        return -3; // Couldn't bind parameters
    }
 
    if (sqlite3_step(stmt) != SQLITE_DONE) { // Execute the insert query
        return -4; // Couldn't execute the query
    }
 
    sqlite3_finalize(stmt); // Finalize the statement handler
    sqlite3_close(db); // Close the database connection
 
    return 0; // Success
}