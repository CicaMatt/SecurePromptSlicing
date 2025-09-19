#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void buy_order(MYSQL *conn, const char* stock_name, int quantity) {
    char query[256];
    
    snprintf(query, sizeof(query), "INSERT INTO stocks (name, quantity) VALUES ('%s', %d);", 
             mysql_real_escape_string(conn, conn->net.strdup(stock_name)), quantity);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Stock order inserted successfully.\n");
    }
}

int main() {
    MYSQL *conn;
    char stock_name[100];
    int quantity;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_order(conn, stock_name, quantity);

    if (mysql_close(conn)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    
    // Simulate redirection
    printf("Redirecting to stock_view page...\n");
    
    return 0;
}