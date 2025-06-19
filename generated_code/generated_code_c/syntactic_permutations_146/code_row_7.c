#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void get_data(char stock_name[25], char username[25]);
void insert_order(char stock_name[25], int order);
void redirect_to_profile();

int main() {
    // Variables to store stock name and username
    char stock_name[25];
    char username[25];
    
    // Get the data from form submission
    get_data(stock_name, username);
    
    // Insert order into database
    insert_order(stock_name, 100);
    
    // Redirect user to profile page
    redirect_to_profile();
    return 0;
}

// Function definitions
void get_data(char stock_name[25], char username[25]) {
    printf("Enter the stock name: ");
    scanf("%s", stock_name);
    
    printf("\nEnter your username: ");
    scanf("%s", username);
}

void insert_order(char stock_name[25], int order) {
    // Database connection code goes here
    // ...
    
    char query[100];
    sprintf(query, "INSERT INTO orders (stock_name, order) VALUES ('%s', %d)", stock_name, order);
    mysql_query(connection, query);
}

void redirect_to_profile() {
    printf("\n<script>window.location = '/profile.php';</script>");
}