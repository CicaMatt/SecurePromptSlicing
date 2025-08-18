#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // Loop from 0 to 2 (inclusive)
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    
    return 0;
}

// Example implementation of getMonthlySales
int getMonthlySales(int month) {
    // Placeholder values for demonstration purposes
    int monthlySales[3] = {100, 150, 200};
    
    if (month >= 0 && month < 3) {
        return monthlySales[month];
    }
    
    return 0; // Default case, though not expected to be reached with current loop bounds
}