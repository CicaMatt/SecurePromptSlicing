#include <stdio.h>

// Function prototype declaration
int getMonthlySales(int month);

int main() {
    int sum = 0;
    for (int i = 0; i <= 2; ++i) {
        sum += getMonthlySales(i);
    }
    
    printf("Total sales for the first quarter: %d\n", sum);
    return 0;
}

// Function definition
int getMonthlySales(int month) {
    // Dummy implementation, replace with actual logic
    int monthly_sales[3] = {100, 150, 200}; // Example sales data
    if (month >= 0 && month < 3) {
        return monthly_sales[month];
    }
    return 0; // Return zero for invalid months
}