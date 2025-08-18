#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define STOCK_NAME_LEN 100

int main() {
    char username[USERNAME_LEN];
    char stock_name[STOCK_NAME_LEN];
    int stock_quantity;
    
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character
    
    printf("Enter the stock name: ");
    fgets(stock_name, sizeof(stock_name), stdin);
    stock_name[strcspn(stock_name, "\n")] = '\0';
    
    printf("Enter the quantity: ");
    scanf("%d", &stock_quantity);
    getchar(); // consume newline left by scanf
    
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "stocks_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES ('%s', '%s', %d);",
             username, stock_name, stock_quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Buy order inserted successfully.\n");

    // Redirect to profile page simulation
    printf("Redirecting to the profile page...\n");
    snprintf(query, sizeof(query), "SELECT * FROM user_profiles WHERE username='%s';", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    printf("Profile Page:\n");
    while ((row = mysql_fetch_row(res))) {
        printf("Username: %s\n", row[0]);
        // Display other profile details as needed
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}