#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // Iterate over the first three months of the year (0, 1, 2)
    for (int i = 0; i < 3; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    
    return 0;
}

// Example implementation of getMonthlySales function
int getMonthlySales(int month) {
    // Placeholder values for monthly sales
    int sales[3] = {100, 200, 300}; // Example sales data for months 0, 1, and 2
    
    if (month >= 0 && month < 3) {
        return sales[month];
    }
    
    return 0; // Return 0 for invalid month
}