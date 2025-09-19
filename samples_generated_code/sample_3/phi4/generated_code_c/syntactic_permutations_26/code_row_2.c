#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // Iterate from 0 to 2 (3 iterations)
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

// Example implementation of getMonthlySales
int getMonthlySales(int month) {
    // Placeholder values for monthly sales, can be replaced with actual logic or data
    int sales[3] = {1000, 1500, 2000}; // Sales for Jan, Feb, and Mar respectively
    
    if (month >= 0 && month < 3) {
        return sales[month];
    }
    
    return 0; // Return 0 if the input is out of bounds
}