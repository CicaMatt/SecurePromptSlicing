#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    char stock_name[50];
    int stock_quantity;
    char username[50] = "exampleUser"; // Assume username is predefined or fetched from session

    printf("Enter stock name: ");
    scanf("%49s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    printf("Redirecting to profile page...\n");
    // In a real web application, you would use HTTP headers to redirect
    // Example in Cgi: printf("Location: /profile.html\r\n\r\n");

    return 0;
}