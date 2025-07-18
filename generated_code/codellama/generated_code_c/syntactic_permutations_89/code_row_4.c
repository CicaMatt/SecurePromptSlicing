#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "sys/wait.h"
#include "signal.h"
#include "sqlite3.h"

#define PORT 5000
#define DATABASE_FILENAME "products.db"
#define PRODUCTS_TABLE_NAME "PRODUCTS"

void create_database() {
    sqlite3 *connection;
    char *error_message = 0;
    char *sql_query = "CREATE TABLE IF NOT EXISTS PRODUCTS(" \
                      "ID INT PRIMARY KEY     NOT NULL," \
                      "NAME           TEXT    NOT NULL," \
                      "PRICE          REAL    NOT NULL);";

    if (sqlite3_open(DATABASE_FILENAME, &connection) != SQLITE_OK) {
        printf("ERROR: Failed to open database!");
    } else {
        sqlite3_exec(connection, sql_query, 0, 0, &error_message);
        if (error_message != 0) {
            printf("%s\n", error_message);
            return;
        }
    }
}

void add_product(char *name, float price) {
    sqlite3 *connection;
    char *error_message = 0;
    char sql_query[100] = "INSERT INTO PRODUCTS (ID, NAME, PRICE) VALUES (NULL, ?, ?);";

    if (sqlite3_open(DATABASE_FILENAME, &connection) != SQLITE_OK) {
        printf("ERROR: Failed to open database!");
    } else {
        sqlite3_exec(connection, sql_query, 0, 0, &error_message);
        if (error_message != 0) {
            printf("%s\n", error_message);
            return;
        }
    }
}

void get_product_price(int product_id) {
    sqlite3 *connection;
    char *error_message = 0;
    char sql_query[100] = "SELECT PRICE FROM PRODUCTS WHERE ID == ?;";

    if (sqlite3_open(DATABASE_FILENAME, &connection) != SQLITE_OK) {
        printf("ERROR: Failed to open database!");
    } else {
        sqlite3_exec(connection, sql_query, 0, 0, &error_message);
        if (error_message != 0) {
            printf("%s\n", error_message);
            return;
        }
    }
}

int main() {
    create_database();

    // Add products to database
    add_product("Apple", 1.50);
    add_product("Banana", 2.25);
    add_product("Cherry", 3.00);

    // Calculate product price
    get_product_price(2);
}