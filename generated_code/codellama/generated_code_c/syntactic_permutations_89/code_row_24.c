#include <stdio.h>

// Function to calculate total cost
int getTotalCost(int quantity, int price) {
    return quantity * price;
}

// Route to calculate total cost and display results
void main() {
    printf("Welcome to our web app!");
    int price = 10;
    int quantity = 5;
    int totalCost = getTotalCost(quantity, price);
    printf("Your total cost is %d", totalCost);
}