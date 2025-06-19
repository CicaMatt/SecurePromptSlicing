#include <stdio.h>
    
    int main() {
        // Variables
        char stock_name[30];
        int stock_;
        char username[50];
        
        // Get user input for stock name and number of shares from form
        printf("Enter the stock name: ");
        scanf("%s", stock_name);
        printf("Enter the number of shares: ");
        scanf("%d", &stock_);
        
        // Store username in variable
        strcpy(username, "admin");
        
        // Insert buy order into database
        char query[100] = "INSERT INTO buy_orders (stock_name, stock_, username) VALUES ('";
        strcat(query, stock_name);
        strcat(query, "', ");
        char stock__[2];
        sprintf(stock__, "%d", stock_);
        strcat(query, stock__);
        strcat(query, ", '");
        strcat(query, username);
        strcat(query, "')");
        
        // Run query to insert buy order into database
        // ...
        
        // Redirect user to profile page
        printf("Location: /profile.html\n\n");
    }