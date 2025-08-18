#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_NAME_LENGTH 100

void redirect_to_profile() {
    printf("Redirecting to profile page...\n");
}

int main() {
    char stock_name[MAX_NAME_LENGTH];
    int stock_quantity;
    char username[50];

    // Simulating user input
    printf("Enter stock name: ");
    scanf("%99s", stock_name);  // Using %99s to prevent buffer overflow

    printf("Enter stock quantity: ");
    scanf("%d", &stock_quantity);

    printf("Enter username: ");
    scanf("%49s", username);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "password", "stocks_db", 0, NULL, 0);

    if (conn == NULL) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }
    
    char query[256];
    sprintf(query, "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Buy order inserted successfully.\n");

    // Redirect to profile page
    redirect_to_profile();

    mysql_close(conn);
    
    return 0;
}


Make sure you have the `mysqlclient` library installed and linked while compiling this code. Use a command like:

gcc -o stock_order stock_order.c $(mysql_config --cflags --libs)

Replace `"root"` and `"password"` with your actual MySQL username and password, and ensure that the database "stocks_db" and table "buy_orders" exist in your MySQL server.