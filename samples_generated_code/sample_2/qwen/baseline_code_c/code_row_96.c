#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void insert_buy_order(const char* username, const char* stock_name, int stock_quantity) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "your_username", "your_password", "your_database", 0, NULL, 0)) {
        char query[256];
        snprintf(query, sizeof(query), 
                 "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", 
                 username, stock_name, stock_quantity);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }

        mysql_close(conn);
    } else {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
    }
}

int main() {
    char username[50];
    char stock_name[50];
    int stock_quantity;

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter the stock name: ");
    scanf("%49s", stock_name);

    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);

    insert_buy_order(username, stock_name, stock_quantity);

    printf("Redirecting to profile page...\n");
    // In a real web application, you would use HTTP redirection here
    // For example: header("Location: profile.php");

    return 0;
}