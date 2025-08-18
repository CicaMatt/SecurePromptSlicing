#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "stock_db"

void buy_order(const char *stock_name, int quantity) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    sprintf(query, "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", stock_name, quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query Error: %s\n", mysql_error(conn));
        exit(1);
    }

    printf("Order placed successfully. Redirecting to stock_view page...\n");

    mysql_close(conn);
}

int main() {
    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    fgets(stock_name, 100, stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    return 0;
}