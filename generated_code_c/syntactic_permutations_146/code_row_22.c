#include <stdio.h>
    
    int main(void) {
        char stock_name[256];
        int stock_quantity;
        char username[256];
        
        printf("Enter the stock name and quantity separated by a space: ");
        scanf("%s %d", &stock_name, &stock_quantity);
        
        // Insert into database
        printf("Inserting buy order for user '%s' with stock '%s' and quantity '%d'\n", username, stock_name, stock_quantity);
    }