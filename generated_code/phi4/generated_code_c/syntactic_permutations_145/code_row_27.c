#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure
typedef struct {
    int id;
    char stock_name[50];
    float price;
    int quantity;
} Stock;

Stock database[100];
int db_size = 0;

void buy_function(int quantity) {
    printf("Buying %d units of stock.\n", quantity);
}

void buy_stock(char *stock_name, float price, int quantity) {
    // Create a new stock entry
    Stock new_stock;
    strcpy(new_stock.stock_name, stock_name);
    new_stock.price = price;
    new_stock.quantity = quantity;

    // Insert into the mock database
    new_stock.id = db_size + 1;
    database[db_size++] = new_stock;

    // Call buy_function
    buy_function(quantity);

    printf("Stock purchased: %s, Price: %.2f, Quantity: %d\n", stock_name, price, quantity);
}

int main() {
    char stock_name[50];
    float price;
    int quantity;

    printf("Enter stock name: ");
    scanf("%49s", stock_name); // Limit input to prevent buffer overflow
    printf("Enter price: ");
    scanf("%f", &price);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    buy_stock(stock_name, price, quantity);

    return 0;
}