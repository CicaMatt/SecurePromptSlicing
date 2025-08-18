#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void buy_function(int quantity) {
    // Implement the logic for buying stocks here
    printf("Buying %d stocks\n", quantity);
}

void buy_stock() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    int quantity;
    printf("Enter the quantity to buy: ");
    scanf("%d", &quantity);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[100];
    snprintf(query, sizeof(query), "INSERT INTO stocks (quantity) VALUES (%d)", quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    buy_function(quantity);

    mysql_close(conn);
}

int main() {
    buy_stock();
    return 0;
}