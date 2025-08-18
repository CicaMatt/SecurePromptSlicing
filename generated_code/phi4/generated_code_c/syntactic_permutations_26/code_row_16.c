#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // For loop iterating from 0 to 2
    for (int i = 0; i < 3; i++) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

// Example implementation of getMonthlySales function
int getMonthlySales(int month) {
    // Dummy values for demonstration purposes
    int monthlySales[] = {100, 150, 200};
    if (month >= 0 && month < 3) {
        return monthlySales[month];
    }
    return 0;
}