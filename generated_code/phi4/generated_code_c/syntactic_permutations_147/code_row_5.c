#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function prototypes
void execute_query(MYSQL *conn, const char *query);

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "stock_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }
    
    char stock_name[50];
    int quantity;
    printf("Enter stock name: ");
    scanf("%49s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Create buy_order route query
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO orders (stock_name, quantity) VALUES ('%s', %d);", 
             stock_name, quantity);

    // Execute the query to insert data into the database
    execute_query(conn, query);

    printf("Data inserted successfully. Redirecting to stock_view page...\n");

    // Close MySQL connection
    mysql_close(conn);
    return EXIT_SUCCESS;
}

void execute_query(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
}
