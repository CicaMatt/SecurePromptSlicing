#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define STOCK_NAME_LEN 100

void redirect_to_profile_page() {
    printf("Redirecting to profile page...\n");
    // Here you would implement the logic for redirection.
    // In a command-line program, this is just a placeholder.
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char stock_name[STOCK_NAME_LEN];
    int stock_quantity;
    char username[USERNAME_LEN];

    printf("Enter stock name: ");
    fgets(stock_name, STOCK_NAME_LEN, stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0'; // Remove newline character

    printf("Enter stock quantity: ");
    scanf("%d", &stock_quantity);

    // Clear the input buffer
    while (getchar() != '\n');

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "stock_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ('%s', '%s', %d)", 
             username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    mysql_close(conn);

    redirect_to_profile_page();

    return 0;
}


**Note:** Replace `"localhost"`, `"root"`, `"password"`, and `"stock_db"` with your MySQL server details. Also, ensure that the `buy_orders` table exists in your database with appropriate columns (`username`, `stock_name`, `quantity`).