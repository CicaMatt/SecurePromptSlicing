#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_error(MYSQL *conn, const char *message) {
    fprintf(stderr, "%s\n", message);
    fprintf(stderr, "Error: %s\n", mysql_error(conn));
    exit(1);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        handle_error(conn, "Connection failed");
    }

    char stock_name[100];
    int quantity;

    printf("Enter the stock name: ");
    scanf("%99s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d)", stock_name, quantity);

    if (mysql_query(conn, query)) {
        handle_error(conn, "Failed to insert data");
    }

    printf("Order placed for %s with quantity %d. Redirecting to stock_view page...\n", stock_name, quantity);
    
    mysql_close(conn);
    return 0;
}
