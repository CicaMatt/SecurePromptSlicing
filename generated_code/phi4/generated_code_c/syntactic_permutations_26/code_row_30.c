#include <stdio.h>

int getMonthlySales(int month) {
    // Placeholder implementation for demonstration purposes.
    // Replace this logic as needed to reflect actual sales data retrieval.
    int monthlyData[] = {100, 150, 200}; // Example sales data for months 0, 1, and 2
    if (month >= 0 && month < sizeof(monthlyData) / sizeof(monthlyData[0])) {
        return monthlyData[month];
    }
    return 0; // Return 0 for invalid month index
}

int main() {
    int sum = 0;
    
    for (int i = 0; i < 3; ++i) {
        sum += getMonthlySales(i);
    }

    printf("Sum of monthly sales: %d\n", sum);
    
    return 0;
}