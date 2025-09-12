#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void executeQuery(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "stock_database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    char stock_name[100];
    int stock_quantity;
    char username[50];

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter stock quantity: ");
    scanf("%d", &stock_quantity);

    printf("Enter username: ");
    scanf("%49s", username);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES ('%s', '%s', %d);",
             username, stock_name, stock_quantity);

    executeQuery(conn, query);

    printf("Redirecting to profile page...\n");
    // Simulate redirection by displaying a message
    char redirect_query[256];
    snprintf(redirect_query, sizeof(redirect_query), "SELECT * FROM users WHERE username = '%s';", username);
    executeQuery(conn, redirect_query);  // This is just for demonstration; actual redirection would be handled on the web server.

    mysql_close(conn);

    return 0;
}