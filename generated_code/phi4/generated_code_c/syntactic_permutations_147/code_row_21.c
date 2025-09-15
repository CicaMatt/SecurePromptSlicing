#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "stockdb"

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        handle_error(conn);
        mysql_close(conn);
        return 1;
    }

    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0'; // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    char query[256];
    snprintf(query, sizeof(query),
             "INSERT INTO buy_orders (stock_name, quantity) VALUES ('%s', %d);",
             stock_name, quantity);

    if (mysql_query(conn, query)) {
        handle_error(conn);
    }

    printf("Order placed successfully.\n");

    mysql_close(conn);
    return 0;
}
