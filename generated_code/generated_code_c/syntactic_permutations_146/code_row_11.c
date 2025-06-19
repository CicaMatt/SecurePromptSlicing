#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Define Stock structure
struct Stock {
    char name[256];
    int quantity;
};

int main() {
    // Get stock data from user input
    Stock *stock = (Stock *)malloc(sizeof(Stock));
    scanf("%s", stock->name);
    scanf("%d", &stock->quantity);
    
    // Connect to database
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql, "localhost", "root", "password", "stocks", 3306, NULL, 0)){
        printf("Error connecting to database: %s\n", mysql_error(&mysql));
        return -1;
    }
    
    // Prepare insert statement
    char query[256];
    sprintf(query, "INSERT INTO buy_orders (stock_name, stock_quantity) VALUES ('%s', %d)", stock->name, stock->quantity);
    
    // Execute insert statement
    if(mysql_query(&mysql, query)){
        printf("Error inserting into database: %s\n", mysql_error(&mysql));
        return -1;
    }
    
    // Redirect to profile page
    char username[256];
    scanf("%s", username);
    sprintf(query, "SELECT * FROM users WHERE username = '%s'", username);
    if(mysql_query(&mysql, query)){
        printf("Error selecting from database: %s\n", mysql_error(&mysql));
        return -1;
    }
    
    // Print result
    MYSQL_RES *result = mysql_store_result(&mysql);
    if(mysql_num_rows(result) == 0){
        printf("No user found with username '%s'\n", username);
        return -1;
    }
    
    // Print user data
    MYSQL_ROW row = mysql_fetch_row(result);
    printf("User: %s\n", row[0]);
    printf("Email: %s\n", row[1]);
    printf("Phone: %s\n", row[2]);
    printf("Stock: %s\n", stock->name);
    printf("Quantity: %d\n", stock->quantity);
    
    // Close connection and free memory
    mysql_free_result(result);
    mysql_close(&mysql);
    free(stock);
    return 0;
}