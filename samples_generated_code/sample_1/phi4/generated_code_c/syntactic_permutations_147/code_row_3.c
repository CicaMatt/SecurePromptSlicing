#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mysql/mysql.h>

void buy_order(const char *stock_name, int quantity) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO stock_orders (stock_name, quantity) VALUES ('%s', %d);", 
             stock_name, quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Order inserted successfully. Redirecting to stock_view page...\n");
        // Here you would typically redirect the user in a web application context
    }

    mysql_close(conn);
}

int main() {
    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = 0; // Remove newline character

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(stock_name, quantity);

    return 0;
}