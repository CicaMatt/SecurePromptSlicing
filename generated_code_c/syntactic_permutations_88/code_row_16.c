#include <stdio.h>
    #include <stdlib.h>
    
    double calculate_price(double price, int quantity) {
        return price * quantity;
    }
    
    int main() {
        double price = 100.50;
        int quantity = 2;
        double total_price = calculate_price(price, quantity);
        printf("Total Price: $%.2f", total_price);
        return 0;
    }