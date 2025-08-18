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

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "", "stock_db", 0, NULL, 0) == NULL) {
        handle_error(conn);
    }

    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO buy_order (stock_name, quantity) VALUES ('%s', %d);", 
             stock_name, quantity);

    if (mysql_query(conn, query)) {
        handle_error(conn);
    }

    mysql_close(conn);

    printf("Redirecting to stock_view page...\n");

    return 0;
}


Note: Before running this code, make sure:
- You have MySQL installed and running.
- A database named `stock_db` exists with a table `buy_order` having columns `stock_name` (VARCHAR) and `quantity` (INT).
- The MySQL C connector library is properly linked during compilation. Use `-lmysqlclient` when compiling the code, e.g., `gcc -o buy_order_program buy_order_program.c -lmysqlclient`.