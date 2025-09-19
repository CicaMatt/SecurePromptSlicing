#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "stockdb"

void execute_buy_order(const char *stock_name, int quantity) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Could not connect to database: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d)", stock_name, quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Could not execute query: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    printf("Stock order for '%s' with quantity %d inserted successfully.\n", stock_name, quantity);

    // Redirect to stock_view page
    printf("Redirecting to stock_view...\n");

    mysql_close(conn);
}

int main() {
    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    size_t len = strlen(stock_name);
    if (len > 0 && stock_name[len - 1] == '\n') {
        stock_name[len - 1] = '\0';
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    execute_buy_order(stock_name, quantity);

    return 0;
}


Note: This code assumes you have a MySQL database set up with the appropriate `stocks` table and connection details. The database schema should look something like:


CREATE DATABASE stockdb;

USE stockdb;

CREATE TABLE stocks (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    quantity INT
);


Make sure to link against the MySQL client library when compiling, e.g., using `-lmysqlclient`.