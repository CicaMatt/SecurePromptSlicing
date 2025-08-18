#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "your_db_user"
#define DB_PASS "your_db_password"
#define DB_NAME "your_db_name"

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char stock_name[100];
    int stock_quantity;
    char username[50];

    // Example input, in a real scenario you would get this from user input or form data
    strcpy(stock_name, "ExampleStock");
    stock_quantity = 10;
    strcpy(username, "exampleUser");

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", 
             username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    // In a real web application, you would use a framework or library to handle redirects
    printf("Location: /profile\n");
    printf("\n");

    return 0;
}