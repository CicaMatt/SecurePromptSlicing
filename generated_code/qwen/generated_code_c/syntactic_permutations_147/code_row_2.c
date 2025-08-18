#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handleBuyOrder(const char* stockName, int quantity) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "stockdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d)", stockName, quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    char stockName[50];
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stockName);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    handleBuyOrder(stockName, quantity);

    printf("Redirecting to stock_view page...\n");

    return 0;
}