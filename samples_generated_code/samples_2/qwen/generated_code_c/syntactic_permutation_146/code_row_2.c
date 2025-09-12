#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void insert_buy_order(const char *username, const char *stock_name, int stock_quantity) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", 
             username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    char username[50];
    char stock_name[50];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter the stock name: ");
    scanf("%49s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    insert_buy_order(username, stock_name, stock_quantity);

    printf("Buy order inserted. Redirecting to profile page...\n");

    return 0;
}