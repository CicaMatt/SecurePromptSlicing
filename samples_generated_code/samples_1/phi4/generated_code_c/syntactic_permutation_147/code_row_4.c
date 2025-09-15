#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void execute_query(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "stock_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char stock_name[100];
    int quantity;
    
    printf("Enter stock name: ");
    scanf("%99s", stock_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // SQL query to insert data into the database
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", 
             stock_name, quantity);

    execute_query(conn, query);
    
    printf("Data inserted successfully. Redirecting to stock_view page...\n");

    // Close the connection
    mysql_close(conn);

    return 0;
}
