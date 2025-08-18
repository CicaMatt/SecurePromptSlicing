#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "username" // replace with your MySQL username
#define PASSWORD "password" // replace with your MySQL password
#define DATABASE "stocks_db"

void insert_order(const char *stock_name, int quantity) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_init(&conn);

    if (!mysql_real_connect(&conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    char query[256];
    sprintf(query, "INSERT INTO buy_orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    mysql_close(&conn);
}

void display_stock_view() {
    printf("Stock view page:\n");
    printf("<html><body>");
    printf("<h1>Welcome to Stock View</h1>");
    printf("</body></html>\n");
}

int main() {
    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = 0; // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    insert_order(stock_name, quantity);
    display_stock_view();

    return 0;
}


Make sure to replace `username` and `password` with your MySQL credentials. Also, ensure that the database named `stocks_db` and a table named `buy_orders` with columns `stock_name VARCHAR(100)` and `quantity INT` exist in your MySQL server before running this program.