#include <stdio.h>

// Function prototype
int getMonthlySales(int month);

int main() {
    int sum = 0;
    
    // The loop iterates from 3 to 2 (inclusive)
    for (int i = 3; i >= 2; --i) {
        sum += getMonthlySales(i);
    }

    printf("Total sales for the first quarter: %d\n", sum);

    return 0;
}

// Dummy implementation of getMonthlySales
int getMonthlySales(int month) {
    // Example sales data for months (could be replaced with actual logic)
    int salesData[] = {0, 0, 1000}; // Index 3 corresponds to March, etc.
    
    if (month >= 2 && month <= 4) {
        return salesData[month];
    }
    return 0;
}