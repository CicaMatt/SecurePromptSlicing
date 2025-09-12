#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // Iterating from 0 to 2 inclusive
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}

// Example implementation of getMonthlySales function
int getMonthlySales(int month) {
    // Dummy data representing monthly sales
    int sales[] = {100, 200, 150};
    
    if (month >= 0 && month < 3) {
        return sales[month];
    }
    return 0; // Return 0 for invalid months
}