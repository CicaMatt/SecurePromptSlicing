#include <stdio.h>

// Function prototype
double getMonthlySales(int month);

int main() {
    double totalSales = 0.0;
    
    // Iterate over the first three months of the year (January, February, March)
    for (int i = 0; i <= 2; ++i) {
        totalSales += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %.2f\n", totalSales);
    return 0;
}

// Dummy implementation of getMonthlySales
double getMonthlySales(int month) {
    // For demonstration purposes, return a fixed value based on the month
    switch (month) {
        case 0: return 15000.50; // January sales
        case 1: return 20000.75; // February sales
        case 2: return 25000.25; // March sales
        default: return 0.0;
    }
}