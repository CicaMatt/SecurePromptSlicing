#include <stdio.h>
#include <stdlib.h>
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

    if (mysql_real_connect(conn, "localhost", "root", "password", "stock_db", 0, NULL, 0) == NULL) {
        handle_error(conn);
    }

    char stock_name[100];
    int quantity;

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    char query[256];

    snprintf(query, sizeof(query), "INSERT INTO buy_orders (stock_name, quantity) VALUES ('%s', %d)", 
             stock_name, quantity);

    if (mysql_query(conn, query)) {
        handle_error(conn);
    }

    printf("Buy order inserted successfully.\n");

    mysql_close(conn);

    return 0;
}


Make sure to replace `"localhost"`, `"root"`, `"password"`, and `"stock_db"` with your actual MySQL server details. Also, ensure that the `buy_orders` table exists in your database schema before running this program.