#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char stock_name[100];
    int stock_quantity;
    char username[] = "example_user"; // Assuming the username is predefined or passed

    printf("Enter Stock Name: ");
    scanf("%99s", stock_name);

    printf("Enter Quantity: ");
    scanf("%d", &stock_quantity);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO stocks (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);

    printf("Redirecting to profile page...\n");
    // In a real web application, you would use HTTP headers to redirect
    // For example: header("Location: profile.html");

    return 0;
}