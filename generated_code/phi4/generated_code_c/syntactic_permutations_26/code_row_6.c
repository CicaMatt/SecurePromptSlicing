#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // Iterate from 0 to 2 (3 iterations)
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

// Example implementation of getMonthlySales function
int getMonthlySales(int month) {
    // Dummy data representing monthly sales
    int sales[] = {100, 150, 200};
    
    // Check if month is within valid range and return corresponding sales value
    if (month >= 0 && month <= 2) {
        return sales[month];
    }
    
    // Return 0 for invalid months as a default case
    return 0;
}