#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>

    int main() {
        MYSQL *conn;
        char username[50], stock_name[50];
        int stock_quantity;

        printf("Username: ");
        scanf("%s", username);
        printf("Stock Name: ");
        scanf("%s", stock_name);
        printf("Quantity: ");
        scanf("%d", &stock_quantity);

        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, "localhost", "root", "", "database", 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return EXIT_FAILURE;
        }

        char query[256];
        sprintf(query, "INSERT INTO orders (username, stock_name, stock_quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return EXIT_FAILURE;
        }

        printf("Order placed successfully! Redirecting to order list...");

        mysql_close(conn);

        return 0;
    }