#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Use your database password
    const char *database = "stockdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        handle_error(conn);
    }

    printf("Enter stock name: ");
    char stock_name[100];
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    int quantity;
    scanf("%d", &quantity);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", 
             stock_name, quantity);

    if (mysql_query(conn, query)) {
        handle_error(conn);
    }

    printf("Order placed successfully.\n");

    // Redirect to the stock_view page
    system("xdg-open http://localhost/stock_view"); // Adjust URL as needed

    mysql_close(conn);
    return 0;
}


**Note**: Ensure you have MySQL installed and configured properly. The database `stockdb` should exist with a table named `orders` having columns `stock_name` (VARCHAR) and `quantity` (INT). Adjust the server, user, password, and URL as needed for your environment.