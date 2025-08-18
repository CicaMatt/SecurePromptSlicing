#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_NAME_LENGTH 100

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
}

int main() {
    MYSQL conn;
    char stock_name[MAX_NAME_LENGTH];
    int stock_quantity;

    // Initialize MySQL connection
    if (mysql_init(&conn) == NULL) {
        handle_error(NULL);
    }

    // Connect to the database
    if (!mysql_real_connect(&conn, "localhost", "root", "password", "stock_db", 0, NULL, 0)) {
        handle_error(&conn);
    }

    printf("Enter stock name: ");
    fgets(stock_name, MAX_NAME_LENGTH, stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter quantity: ");
    scanf("%d", &stock_quantity);

    // Construct the SQL query
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO stocks (stock_name, stock_quantity) VALUES ('%s', %d);",
             mysql_real_escape_string(&conn, strdup(stock_name)), stock_quantity);

    // Execute the SQL query
    if (mysql_query(&conn, query)) {
        handle_error(&conn);
    }

    printf("Stock added successfully. Redirecting to profile page...\n");

    // Close MySQL connection
    mysql_close(&conn);

    // Simulate redirection (In a real application, this would be handled by the web server)
    system("xdg-open https://example.com/profile"); // Replace with your actual URL

    return 0;
}


**Note:** Before running this code, ensure that you have MySQL installed and properly configured. You also need to replace `"localhost"`, `"root"`, `"password"`, and `"stock_db"` with your database host, username, password, and database name respectively. Additionally, the redirection URL should be replaced with your actual profile page URL.