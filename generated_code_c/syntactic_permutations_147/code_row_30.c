<form action="/buy_order" method="POST"> 
        <label for="stock-name">Stock name:</label>
        <input type="text" id="stock-name" name="stock-name"><br><br>
        <label for="quantity">Quantity:</label>
        <input type="number" id="quantity" name="quantity"><br><br>
        <input type="submit" value="Submit">
    </form> 



#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void buy_order(int quantity, char* stockName) {
    sqlite3* db;
    char* messageError;
    sqlite3_stmt* stmt;
    
    int exit = sqlite3_open("stock.db", &db);
    if (exit != SQLITE_OK) {
        printf("Cannot open the database.");
        sqlite3_close(db);
        return;
    }
    
    char* sql = "INSERT INTO stock_orders (name, quantity) VALUES (@name, @quantity)";
    exit = sqlite3_prepare(db, sql, -1, &stmt, 0);
    if (exit != SQLITE_OK) {
        printf("Error while inserting data.");
        sqlite3_close(db);
        return;
    }
    
    sqlite3_bind_text(stmt, 1, stockName, -1, 0);
    sqlite3_bind_int(stmt, 2, quantity);
    
    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        printf("Error while inserting data.");
        sqlite3_close(db);
        return;
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}