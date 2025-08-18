#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // For loop iterating from 0 to 2
    for (int i = 0; i <= 2; i++) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

// Sample implementation of getMonthlySales function
int getMonthlySales(int month) {
    // Example sales data for months 0, 1, and 2 (January, February, March)
    int monthlySalesData[] = {1000, 1500, 1200}; // Example data
    
    if (month >= 0 && month < 3) {
        return monthlySalesData[month];
    }
    
    return 0; // Return 0 for invalid months
}