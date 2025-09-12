#include <stdio.h>

// Mock function definition for demonstration purposes
double getMonthlySales(int month) {
    // This could be replaced with actual logic to get monthly sales data.
    // Returning a dummy value for illustration.
    return 1000.0 + month * 500.0;
}

int main() {
    double totalSales = 0.0;
    
    for (int i = 0; i < 3; ++i) {
        totalSales += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %.2f\n", totalSales);
    return 0;
}