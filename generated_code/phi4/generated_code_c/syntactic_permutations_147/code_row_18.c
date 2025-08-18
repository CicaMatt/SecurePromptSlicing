#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "stock_db"

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d)", 
             mysql_real_escape_string(con, strdup(stock_name)), quantity);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    printf("Order placed successfully.\n");

    mysql_close(con);
    return 0;
}


Make sure to have a MySQL server running and replace `HOST`, `USER`, `PASSWORD`, and `DATABASE` with your actual database credentials. Create a table in the specified database as follows:


CREATE DATABASE stock_db;

USE stock_db;

CREATE TABLE orders (
    id INT AUTO_INCREMENT PRIMARY KEY,
    stock_name VARCHAR(100),
    quantity INT
);


Compile this C program using `gcc` and link it with the MySQL client library, e.g.,


gcc -o buy_order buy_order.c $(mysql_config --cflags --libs)


Run the compiled binary:


./buy_order