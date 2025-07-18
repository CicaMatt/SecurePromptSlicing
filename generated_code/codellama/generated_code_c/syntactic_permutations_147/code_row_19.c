#include <stdio.h>
#include<stdlib.h>
#include <sqlite3.h>   

int buy_order(char *stock, int quantity) {
    sqlite3* db;
    char* errorMessage = 0;
    const char* sql = "INSERT INTO stock (name, quantity) VALUES(?, ?)";
    sqlite3_stmt* stmt;

    if (sqlite3_open("stock.db", &db) != SQLITE_OK) {
        printf("Error opening database\n");
        return 1;
    }

    if (sqlite3_prepare(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    if (sqlite3_bind_text(stmt, 1, stock, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 2, quantity) != SQLITE_OK)
    {
        printf("Error binding parameters\n");
        sqlite3_close(db);
        return 1;
    }

    int result = sqlite3_step(stmt);

    if (result == SQLITE_DONE) {
        printf("%d stock(s) of %s purchased\n", quantity, stock);
    } else {
        printf("Error inserting data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}