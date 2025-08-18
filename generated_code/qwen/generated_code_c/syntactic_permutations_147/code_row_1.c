#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_NAME_LEN 50

void insert_buy_order(const char *stock_name, int quantity) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO buy_orders (stock_name, quantity) VALUES ('%s', %d)", stock_name, quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    char stock_name[MAX_NAME_LEN];
    int quantity;

    printf("Enter the stock name: ");
    fgets(stock_name, MAX_NAME_LEN, stdin);
    stock_name[strcspn(stock_name, "\n")] = 0; // Remove newline character

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    insert_buy_order(stock_name, quantity);

    printf("Redirecting to stock_view page...\n");

    return 0;
}